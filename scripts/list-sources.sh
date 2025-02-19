echo "SRC=	main.cpp \\" >src.mk
ls src/ | tr " " "\n" | sed 's/^/\t\t/; s/$/ \\/' >>src.mk
