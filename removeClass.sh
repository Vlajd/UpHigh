
read -p "Class name: " class

rm ./Source/KaijuGJ2022/$class.cpp
rm ./Source/KaijuGJ2022/$class.h

rm -R ./Binaries/Win64/*

echo "Removed class $class."
