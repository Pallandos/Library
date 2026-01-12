shs(L,LP):-
L = [F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17],
LP = [P11,P12],

fd_domain(L, 0, 1),
fd_domain(LP, 0, 5),
%F0 est la base, donc activée
F0 #= 1,

%F1 à F7 sont obligatoires
F1 #= F0,
F2 #= F0,
F3 #= F0,
F4 #= F0,
F5 #= F0,
F6 #= F0,
F7 #= F0,

%F8 et F9 sont optionelles sous F4
F8 #=< F4,
F9 #=< F4,

%F13 est nécessaire sous F5 et F12 est optionnel
F13 #= F5,
F12 #=< F5,

%F10 et F11 sont optionnelles sous F2
F10 #=< F2,
F11 #=< F2,

%F14 et F15 sont incompatibles, mais l'un des deux est nécessaire sous F7
F14 + F15 #=< F7,

%F16 et F17 sont alternatifs, F17 est obligatoire 
F16 + F17 #=< F6, 
F17 #= F6,

% performances:
F11 #<=> (P11 #> 0),
F12 #<=> (P12 #> 0),
P111 #>= 2*P12,

append(L,LP,LR),
fd_labeling(LR).
