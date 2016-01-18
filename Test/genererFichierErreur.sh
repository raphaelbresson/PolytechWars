make
valgrind --leak-check=full --gen-suppressions=all ./test 2>&1 | egrep "^[{}]|^   [^ \t]" >> erreurs.supp