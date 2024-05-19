build:
	gcc Tema1.c -Wall -lm -o lanParty
run:
	./lanParty date/t$i/c.in date/t$i/d.in out/out$i.out
clean:
	rm -f lanParty
