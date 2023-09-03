for ((i=0; i < 50; i++))
	do
    echo $(cat ./build/test/$i.test | ./build/programm) > ./build/test/$i.res
    if [[ "$(cat ./build/test/$i.res)" == "$(cat ./build/test/$i.answer)" ]];
      then
        echo "Test  $i  successfully passed!"
      else
        echo -e "\033[31mTest  $i  failed! Check result files.\033[0m "
    fi
	done