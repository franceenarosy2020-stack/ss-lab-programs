#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp1, *fp2, *fp3, *fp4;
    char label[20], opcode[20], operand[20];
    char mnemonic[10], code[10], symbol[20];
    int loc, start_addr = 0, operand_address, found;
    char object_code[1000] = "";  // store full text record content
    char temp[30];
    int text_start_addr = 0, text_length = 0;

    fp1 = fopen("out.txt", "r");     // intermediate file
    fp2 = fopen("optab.txt", "r");   // opcode table
    fp3 = fopen("symtbl.txt", "r");  // symbol table
    fp4 = fopen("output.txt", "w");  // final object code output

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening one of the files.\n");
        return 1;
    }

    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);

    // START directive
    if (strcmp(opcode, "START") == 0) {
        start_addr = (int)strtol(operand, NULL, 16);
        fprintf(fp4, "H^%s^%06X^", label, start_addr);
        fscanf(fp1, "%X\t%s\t%s\t%s", &loc, label, opcode, operand);
        text_start_addr = loc;
    }

    // Begin text record
    strcpy(object_code, "");

    while (1) {
        // Stop on END
        if (strcmp(opcode, "END") == 0) {
            break;
        }

        rewind(fp2);
        int opcode_found = 0;

        while (fscanf(fp2, "%s\t%s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                opcode_found = 1;

                rewind(fp3);
                found = 0;
                while (fscanf(fp3, "%s\t%X", symbol, &operand_address) != EOF) {
                    if (strcmp(operand, symbol) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (found)
                    sprintf(temp, "^%s%04X", mnemonic, operand_address);
                else
                    sprintf(temp, "^%s0000", mnemonic); // Undefined symbol

                strcat(object_code, temp);
                text_length += 3;
                break;
            }
        }

        if (!opcode_found) {
            if (strcmp(opcode, "BYTE") == 0) {
                strcat(object_code, "^");

                if (operand[0] == 'C' && operand[1] == '\'') {
                    // Standard C'...' format
                    for (int i = 2; operand[i] != '\'' && operand[i] != '\0'; i++) {
                        sprintf(temp, "%02X", operand[i]);
                        strcat(object_code, temp);
                        text_length += 1;
                    }
                } else if (operand[0] == 'X' && operand[1] == '\'') {
                    // Standard X'...' format
                    for (int i = 2; operand[i] != '\'' && operand[i] != '\0'; i++) {
                        sprintf(temp, "%c", operand[i]);
                        strcat(object_code, temp);
                        text_length += 1;
                    }
                } else if (strlen(operand) == 1) {
                    // Custom shorthand: BYTE Z
                    sprintf(temp, "%02X", operand[0]);
                    strcat(object_code, temp);
                    text_length += 1;
                } else {
                    // Unsupported format — skip
                    strcat(object_code, "??");
                }
            } else if (strcmp(opcode, "WORD") == 0) {
                sprintf(temp, "^%06X", atoi(operand));
                strcat(object_code, temp);
                text_length += 3;
            }
        }

        // Read next line
        if (fscanf(fp1, "%X\t%s\t%s\t%s", &loc, label, opcode, operand) == EOF)
            break;
    }

    // Finalize H record with program length
    int program_length = loc - start_addr;
    fprintf(fp4, "%06X\n", program_length);

    // Write text record
    fprintf(fp4, "T^%06X^%02X%s\n", text_start_addr, text_length, object_code);

    // End record
    fprintf(fp4, "E^%06X\n", start_addr);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
