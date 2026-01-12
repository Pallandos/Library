% =======================================================
% DÉTECTEUR DE DEAD FEATURES PAR CONSTRUCTION DE LISTE
% =======================================================

% Prédicat principal
dead_feature_test_construite :-
    write('--- DEAD FEATURE ANALYSE (Construction Dynamique) ---'), nl,
    
    % On boucle sur les positions 1 à 18 pour le 1 mobile
    (   between(1, 18, Index_fixe),
        
        % 1. Construire la liste L = [1, _, ..., 1 (a Index_fixe), ..., _]
        build_test_list(Index_fixe, L),
        
        % 2. Lancer la recherche de solutions (findall)
        findall(L, shs(L), Semantique),
        
        % 3. Compter les solutions
        length(Semantique, NombreSolutions),
        
        % 4. Affichage du résultat
        Num is Index_fixe - 1, % Pour afficher F0, F1, F2...
        format('Feature F~w (Index ~w) : ~w solutions trouvees.', [Num, Index_fixe, NombreSolutions]),
        (   NombreSolutions =:= 0
        ->  write(' => DEAD FEATURE !!!')
        ;   true
        ),
        nl,
        fail  % Force le backtracking pour tester l'Index suivant
    ;   true
    ),
    write('------------------------------------------------------------'), nl.


% Prédicat auxiliaire pour construire la liste de test
% build_test_list(Index du '1', Liste de Contrainte)
build_test_list(Index_fixe, List) :-
    length(List, 18), % La liste doit avoir 18 éléments
    
    % On parcourt la liste et on instancie les éléments
    build_list_recursive(1, Index_fixe, List).

build_list_recursive(_, _, []). % Cas de base : liste vide

build_list_recursive(Current_Index, Index_fixe, [H|T]) :-
    (   Current_Index =:= Index_fixe % Si on est à la position désirée
    ->  H = 1                         % Fixer l'élément à 1
    ;   H = _                         % Sinon, laisser une variable anonyme (_)
    ),
    Next_Index is Current_Index + 1,
    build_list_recursive(Next_Index, Index_fixe, T).