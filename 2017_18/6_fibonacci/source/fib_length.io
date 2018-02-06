//fib_length.io
//a program to calculate the length of terms of the fibonacci sequence
//part of the PandA1 course at Bristol University
//2015 Conor Houghton conor.houghton@bristol.ac.uk

//To the extent possible under law, the author has dedicated all copyright 
//and related and neighboring rights to this software to the public domain 
//worldwide. This software is distributed without any warranty. 

fib := clone Object
fib last := BigNum clone
fib old_last := BigNum clone

fib last := last + 1

fib advance := method(temp := last; last = last + old_last; old_last = temp)

fib length := method(last asString size)

n0 := 2
n1 := 100000

for(i,n0,n1, 
	     fib advance; 
	     i print; 
	     " " print; 
	     fib length print ; 
	     "\n" print
	     )