% =======================================================
% DÉTECTEUR DE FALSE OPTIONALITIES
% =======================================================

% Prédicat principal
test_false_optionalities :-
    write('--- FALSE OPTIONALITY ANALYSE (Fixation a 0) ---'), nl,
    
    % On ne boucle que sur les features candidates (F8 a F16)
    % F8 est à l'index 9, F16 est à l'index 17.
    % F17 est à l'index 18 mais est obligatoire par F17 #= F6. On le retire pour plus de clarté.
    List_Indices = [9, 10, 11, 12, 13, 15, 16, 17], % F8, F9, F10, F11, F12, F14, F15, F16
    
    (   member(Index_fixe, List_Indices),
        
        % 1. Construire la liste L = [_, _, ..., 0 (a Index_fixe), ..., _]
        build_test_list_zero(Index_fixe, L_Test),
        
        % 2. Lancer la recherche de solutions
        findall(L_Test, shs(L_Test), Semantique),
        
        % 3. Compter les solutions
        length(Semantique, NombreSolutions),
        
        % 4. Affichage du résultat
        Num is Index_fixe - 1, % Pour afficher F8, F9...
        format('Feature F~w (Index ~w) : ~w solutions trouvees.', [Num, Index_fixe, NombreSolutions]),
        (   NombreSolutions =:= 0
        ->  write(' => FALSE OPTIONALITY !!! (En fait Obligatoire)')
        ;   true
        ),
        nl,
        fail  % Force le backtracking pour tester l'Index suivant
    ;   true
    ),
    write('------------------------------------------------------------'), nl.


% Prédicat auxiliaire pour construire la liste de test (avec un 0)
build_test_list_zero(Index_fixe, List) :-
    length(List, 18), % La liste doit avoir 18 éléments
    build_list_recursive_zero(1, Index_fixe, List).

build_list_recursive_zero(_, _, []).

build_list_recursive_zero(Current_Index, Index_fixe, [H|T]) :-
    (   Current_Index =:= Index_fixe % Si on est à la position désirée
    ->  H = 0                         % Fixer l'élément à 0
    ;   H = _                         % Sinon, laisser une variable anonyme (_)
    ),
    Next_Index is Current_Index + 1,
    build_list_recursive_zero(Next_Index, Index_fixe, T).