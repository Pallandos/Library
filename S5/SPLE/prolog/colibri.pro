colibriLP(L):-
L = [F1, F2, F3 ,F4 ,F5 ,F6 ,F7, F8, F9 ,F10 ,F11, F12],

%definir le domaine des variables
F1 #= 1,

%F2, F3, F4 sont mandatory w.r.t. F1 et F7 est mandatory wrt F3
F2 #= F1,
F3 #= F1,
F1 #= F4,
F3 #= F7,

%F5 et F6 sont optionels wrt F3
F3 #>= F5,
F6 #=< F3,

%[1..2] group cardinality in F7
F7*1 #=< F8  + F9 + F10,
F8 + F9 + F10 #=< F7*2,

%relation de excludes entre F2 et F8
F2 * F8 #= 0,

%relation alternative entre F11 et F12 wrt F4
F4 #= F11 + F12,

%F6 implique F12
F6 #==> F12,

%La relation qu'on ne peut pas représenter graphiquement
F9 #==> #\((F5 #/\ F6) #\/ F11),
fd_labeling(L).
