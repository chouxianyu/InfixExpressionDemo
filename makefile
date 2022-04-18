objects = Expression.o BiTNode.o BiTree.o main.o
main : $(objects)
	g++ -o main $(objects)
main.o : BiTree.h
BiTree.o : BiTree.h BiTNode.h Expression.h
BiTNode.o : BiTNode.h Expression.h
Expression.o : Expression.h
clean :
	rm main $(objects)
