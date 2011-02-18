NSC=../code/NSC

.SECONDEXPANSION:

sample:
	d=n1000.s10.c100.i100; make $$d ; echo == ; cat $${d}.summary


n%: argN=$(subst n,,$(word 1,$(subst ., ,$@)))
n%: argS=$(subst s,,$(word 2,$(subst ., ,$@)))
n%: argC=$(subst c,,$(word 3,$(subst ., ,$@)))
n%: argI=$(subst i,,$(word 4,$(subst ., ,$@)))

n%:
	echo :${argN}:
	echo :${argS}:
	echo :${argC}:
	echo :${argI}:
	${NSC} ${argN} ${argS} ${argC} ${argI} | egrep 'rca.*col' | cut -d: -f2 > $@.dat
	> $@.summary
	{ echo -ne 'N\tS\tC\t'    ; } >> $@.summary
	{ echo  -e 'minOrphans\tmaxOrphans\toneLCC'    ; } >> $@.summary
	{ echo -ne '${argN}\t${argS}\t${argC}\t'    ; } >> $@.summary
	{ cat $@.dat | cut -d, -f1 | sort -g  | head -n1 | tr -d ' \t' | tr '\n' '\t'; } >> $@.summary
	{ cat $@.dat | cut -d, -f1 | sort -gr | head -n1 | tr -d ' \t' | tr '\n' '\t'; } >> $@.summary
	{ cat $@.dat | cut -d, -f2 | sort -g  | egrep '\b1\b'  | wc -l               ; } >> $@.summary
