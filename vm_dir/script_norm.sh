#!/bin/sh

esc=$(printf '\033')

echo "\033[104mFichier auteur:\033[0m"
if [ -e auteur ]
then
	cat -e auteur
else
	echo "\033[31mPas de fichier auteur\033[0m"
fi
echo "\n\033[104mNORME:\033[0m"
norminette | ( sed "s/Error/${esc}[31mError${esc}[0m/" | sed "s/Warning/${esc}[33mWarning${esc}[0m/")
echo "\n\033[104mOperateurs fin de ligne:\033[0m"
echo "\033[31m" && grep -Hrn "[^\*/][+%\-\*\?=:&|/]$" **/**.c && echo "\033[0m"|| echo "\033[92mOK\033[0m"

echo "\n\033[104mCode dans les defines:\033[0m"
echo "\033[31m" && grep -Hrn "define\(.\?\)*(\|define\(.\?\)*)\|define\(.\?\)*\\[\|define\(.\?\)*\\]" **/**.h && echo "\033[0m" || echo "\033[92mOK\033[0m"

echo "\n\033[104mMAKEFILE:\033[0m"

echo "\n\033[33mRegle name:\033[0m"
grep "^\$(NAME):" Makefile || (echo "\033[31m" && echo "Pas trouve" && echo "\033[0m")
echo "\033[33mRegle clean:\033[0m"
grep "^clean:" Makefile || (echo "\033[31m" && echo "Pas trouve" && echo "\033[0m")
echo "\033[33mRegle fclean\033[0m"
grep "^fclean:" Makefile || (echo "\033[31m" && echo "Pas trouve" && echo "\033[0m")
echo "\033[33mRegle re\033[0m"
grep "^re:" Makefile || (echo "\033[31m" && echo "Pas trouve" && echo "\033[0m")
