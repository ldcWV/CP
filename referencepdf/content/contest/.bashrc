co() {
	g++ -std=c++11 $1.cpp -o $1
}

run() {
	if [ $# -eq 2 ]
		then
			./$1 < $1$2.in
		else
			./$1
		fi
}

crun() {
	co $1 && echo "Compiled!" && run $1 $2
}
