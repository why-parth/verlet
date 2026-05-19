// precompiler {

//         char find[4] = "int";
//         char replace[5] = "char";
//         char fileline[1024];
//         char newline[1024];
//         char * pos;
//         char * pos_int;
//         int is_token = 0;

//         while ( fgets(fileline, sizeof(fileline), fileout) ) {
//             pos = fileline;
//             newline[0] = '\0';
//             while (strchr(pos, '=') && (pos_int = strstr(pos, find))) {
//                 is_token = __is_token_at(fileline, strlen(fileline), pos_int - fileline, strlen(find));
//                 if (!is_token) {
//                     strncat(newline, pos, pos_int - pos);
//                     strcat(newline, find);
//                     pos = pos_int + sizeof(find) - 1;
//                     continue;
//                 }
//                 strncat(newline, pos, pos_int - pos);
//                 strcat(newline, replace);
//                 pos = pos_int + strlen(find);
//             }
//             strcat(newline, pos);
//             fputs(newline, filein);
//         }

// }

// #include precompilation
// #define openfile(_path)
