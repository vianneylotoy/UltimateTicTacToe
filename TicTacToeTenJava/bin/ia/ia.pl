-set_prolog_flag(toplevel_print_options, [max_depth(0)]).
-set_prolog_flag(gc, off).
 
:- use_module(library(lists)).
:-set_prolog_flag(toplevel_print_options,[max_depth(0)]).
:- use_module(library(random)).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%      Vrai si la case N du SousPlateau est de ce Signe #terminer.(utilisé par jouerCoup).         
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

signeCaseSousPlateau(N, SousPlateau, Signe) :-
        nth1(N, SousPlateau, Signe).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%      Change la case N d'un sous plateau par le signe 
%         #terminer.(Utilisé par jouerCoup).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

changeSigneCase(1, [_|SousPlateau], Signe, [Signe|SousPlateau]).
changeSigneCase(N, [X|SousPlateau], Signe, [X|NSousPlateau]) :-
        N2 is N - 1,
        changeSigneCase(N2, SousPlateau, Signe, NSousPlateau).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%     Vérification du Gagnant #terminer.        
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sousplateauGagnant([Signe,Signe,Signe|_],Signe):-!. % write('The winner is '),write(Signe).
sousplateauGagnant([_,_,_,Signe,Signe,Signe|_],Signe):-!.
sousplateauGagnant([_,_,_,_,_,_,Signe,Signe,Signe|_],Signe):-!.
sousplateauGagnant([Signe,_,_,_,Signe,_,_,_,Signe],Signe):-!.
sousplateauGagnant([_,_,Signe,_,Signe,_,Signe,_,_],Signe):-!.
sousplateauGagnant([Signe,_,_,Signe,_,_,Signe,_,_],Signe):-!.
sousplateauGagnant([_,Signe,_,_,Signe,_,_,Signe,_],Signe):-!.
sousplateauGagnant([_,_,Signe,_,_,Signe,_,_,Signe],Signe).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Détermine le type de coup (d : Continue, g : GAGNANT, n : NULLE, p : PERDANT) avec le nouveau plateau suite au coup joué
% Signe : le signe de notre joueur
% Tour : Numéro du tour de la partie (nb de coups joués au total)
% TourMax : Nombre de tours maximal dans une partie (81)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

typeCoup(Plateau, _Signe, SigneAdv, _Tour, _TourMax,  p) :-
        sousplateauGagnant(Plateau, SigneAdv),
        !.
typeCoup(Plateau, Signe, _SigneAdv, _Tour, _TourMax, g) :-
        sousplateauGagnant(Plateau, Signe),
        !.
typeCoup(_Plateau, _Signe, _SigneAdv, TourMax, TourMax, n) :- !.
typeCoup(_Plateau, _Signe, _SigneAdv, _Tour, _TourMax, d).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%       Place le signe sur le sous - plateau donné
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

genereCoup(N,Plateau,Signe,NotreSigne,SigneAdv,Tour,TourMax,TypeCoup,NPlateau):-
        signeCaseSousPlateau(N, Plateau, v),
        changeSigneCase(N,Plateau,Signe,NPlateau),
        signeCaseSousPlateau(N, NPlateau, Signe),
        typeCoup(NPlateau,NotreSigne,SigneAdv,Tour,TourMax, TypeCoup).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Renvoie la liste de tous les coups possibles à partir d'un plateau
% sous la forme d'une liste contenant le nouveau plateau, la case et
% le signe de la case
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

plateauxSuivants(Plateau, SigneCoup, SigneJoueur, SigneAdv, Tour, TourMax, R) :-
        findall([NPlateau, Case, TypeCoup], genereCoup(Case, Plateau, SigneCoup, SigneJoueur, SigneAdv, Tour, TourMax, TypeCoup, NPlateau), R).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Fonction d'évaluation.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Cree une liste de 5 éléments contenant N fois ce Signe
creerListeSigne(1, Signe, [Signe,_,_]).
creerListeSigne(2, Signe, [Signe,Signe,_]).
creerListeSigne(3, Signe, [Signe,Signe,Signe]).


% R = 1 si la ligne du Plateau débutant (de gauche à droite) par Dep contient N fois ce Signe
nbSigneLigne(SousPlateau, Dep, Signe, N, 1) :-
        Dep2 is Dep + 1,
        Dep3 is Dep + 2,
        nth1(Dep, SousPlateau, C1),
        nth1(Dep2, SousPlateau, C2),
        nth1(Dep3, SousPlateau, C3),
        creerListeSigne(N, Signe, L),
        permutation(L, [C1,C2,C3]),
        !.

nbSigneLigne(_, _, _, _, 0).

% R = 1 si la colonne du Plateau débutant (de haut en bas) par Dep contient N fois ce Signe
nbSigneCol(Plateau, Dep, Signe, N, 1) :-
        Dep2 is Dep + 3,
        Dep3 is Dep + 6,
        nth1(Dep, Plateau, C1),
        nth1(Dep2, Plateau, C2),
        nth1(Dep3, Plateau, C3),
        creerListeSigne(N, Signe, L),
        permutation(L, [C1,C2,C3]),
        !.
nbSigneCol(_, _, _, _, 0).

% R = 1 si la diagonale du Plateau débutant à la case 1 contient N fois ce Signe
nbSigneDiag1(Plateau, Signe, N, 1) :-
        Dep is 1,
        Dep2 is Dep + 4,
        Dep3 is Dep + 8,
        nth1(Dep, Plateau, C1),
        nth1(Dep2, Plateau, C2),
        nth1(Dep3, Plateau, C3),
        creerListeSigne(N, Signe, L),
        permutation(L, [C1,C2,C3]),
        !.
nbSigneDiag1(_, _, _, 0).

% R = 1 si la diagonale du Plateau débutant à la case 5 contient N fois ce Signe
nbSigneDiag2(Plateau, Signe, N, 1) :-
        Dep is 3,
        Dep2 is Dep + 2,
        Dep3 is Dep + 4,
        nth1(Dep, Plateau, C1),
        nth1(Dep2, Plateau, C2),
        nth1(Dep3, Plateau, C3),
        creerListeSigne(N, Signe, L),
        permutation(L, [C1,C2,C3]),
        !.
nbSigneDiag2(_, _, _, 0).

nbNSigne(Plateau, Signe, N, R):-
        nbSigneLigne(Plateau, 1, Signe, N, R1),
        nbSigneLigne(Plateau, 4, Signe, N, R2),
        nbSigneLigne(Plateau, 7, Signe, N, R3),
        nbSigneCol(Plateau, 1, Signe, N, R4),
        nbSigneCol(Plateau, 2, Signe, N, R5),
        nbSigneCol(Plateau, 3, Signe, N, R6),
        nbSigneDiag1(Plateau, Signe, N, R7),
        nbSigneDiag2(Plateau, Signe, N, R8),
        R is R1 + R2 + R3  + R4 + R5 + R6 + R7 + R8.

% Vrai si le Plateau contient R lignes/colonnes/diagonales comportant 1 fois ce Signe
nb1Signe(Plateau, Signe, R) :-
        nbNSigne(Plateau, Signe, 1, R).

% Vrai si le Plateau contient R lignes/colonnes/diagonales comportant 2 fois ce Signe
nb2Signe(Plateau, Signe, R) :-
        nbNSigne(Plateau, Signe, 2, R).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fonction d'évaluation d'un plateau
% 1000 si plateau gagnant, -1000 si perdant, 0 si match nul
% Sinon : f(Plateau) = 2 * (NB2 - NB2Adv) + 1 * (NB1 - NB1Adv)
% Avec NB2 : nb de lignes/col/diag comportant 2 fois notre Signe
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
evalue([_,_,p], _SigneJoueur, _SigneAdv, Prof, Eval) :- 
        Eval is -1000 + Prof,
        !.
evalue([_,_,g], _SigneJoueur, _SigneAdv, Prof, Eval) :-
        Eval is 1000 - Prof,
        !.
evalue([_,_,n], _SigneJoueur, _SigneAdv, _Prof, 0) :- !.
evalue([Plateau,_,_], SigneJoueur, SigneAdv, _Prof, Eval) :-
        nb2Signe(Plateau, SigneJoueur, NB2),
        nb2Signe(Plateau,SigneAdv, NB2Adv),
        nb1Signe(Plateau, SigneJoueur, NB1),
        nb1Signe(Plateau,SigneAdv, NB1Adv),
        Eval is  2 * (NB2 - NB2Adv) + 1 * (NB1 - NB1Adv).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%       ALGORTHME ALPHA-BETA
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

minCoups([], Meilleur, Meilleur).
minCoups([[Coup,Eval]|L], [_MeillCoupActuel,MeillEvalActuel], [MeillCoup,MeillEval]) :-
        Eval =< MeillEvalActuel,
        minCoups(L, [Coup,Eval], [MeillCoup,MeillEval]),
        !.

minCoups([_|L], [MeillCoupActuel,MeillEvalActuel], [MeillCoup,MeillEval]) :-
        minCoups(L, [MeillCoupActuel,MeillEvalActuel], [MeillCoup,MeillEval]).

maxCoups([], Meilleur, Meilleur).
maxCoups([[Coup,Eval]|L], [_MeillCoupActuel,MeillEvalActuel], [MeillCoup,MeillEval]) :-
        Eval >= MeillEvalActuel,
        maxCoups(L, [Coup,Eval], [MeillCoup,MeillEval]),
        !.

maxCoups([_|L], [MeillCoupActuel,MeillEvalActuel], [MeillCoup,MeillEval]) :-
        maxCoups(L, [MeillCoupActuel,MeillEvalActuel], [MeillCoup,MeillEval]).

minEvalPlateaux([], _SigneJoueur, _SigneAdv, _Tour, _TourMax, _Prof, _ProfParcourue, _Alpha, _Beta, Acc, Acc).
minEvalPlateaux([[_Plateau,_Case,_Type]|_L], _SigneJoueur, _SigneAdv, _Tour, _TourMax, _Prof, _ProfParcourue, Alpha, Beta, Acc, Acc) :-
        Alpha >= Beta,
        !.
    
minEvalPlateaux([[Plateau,Case,Type]|L], SigneJoueur, SigneAdv, Tour, TourMax, 0, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        evalue([Plateau,Case,Type], SigneJoueur, SigneAdv, ProfParcourue, Eval),
        max_member(Alpha2, [Alpha,Eval]),
        minEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, 0, ProfParcourue, Alpha2, Beta, [[[Plateau,Case,Type],Eval]|Acc], CoupsEvalues),
        !.

minEvalPlateaux([[Plateau,Case,g]|L], SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        evalue([Plateau,Case,g], SigneJoueur, SigneAdv, ProfParcourue, Eval),
        max_member(Alpha2, [Alpha,Eval]),
        minEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha2, Beta, [[[Plateau,Case,g],Eval]|Acc], CoupsEvalues),
        !.

minEvalPlateaux([[Plateau,Case,p]|L], SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        evalue([Plateau,Case,p], SigneJoueur, SigneAdv, ProfParcourue, Eval),
        max_member(Alpha2, [Alpha,Eval]),
        minEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha2, Beta, [[[Plateau,Case,p],Eval]|Acc], CoupsEvalues),
        !.

minEvalPlateaux([[Plateau,Case,Type]|L], SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        plateauxSuivants(Plateau, SigneAdv, SigneJoueur, SigneAdv, Tour, TourMax, R),
        Prof2 is Prof - 1,
        ProfParcourue2 is ProfParcourue + 1,
        maxEvalPlateaux(R, SigneJoueur, SigneAdv, Tour, TourMax, Prof2, ProfParcourue2, Alpha, Beta, [], CoupsMaxEvalues),
        minCoups(CoupsMaxEvalues, [_,1000], [_MeillCoup,MeillEval]),
        max_member(Alpha2, [Alpha,MeillEval]),
        minEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha2, Beta, [[[Plateau,Case,Type],MeillEval]|Acc], CoupsEvalues).



% CoupsEvalues = [[Plateau, CaseDepart, CaseArrivee, SigneCube, Type], Eval]
maxEvalPlateaux([], _SigneJoueur, _SigneAdv, _Tour, _TourMax, _Prof, _ProfParcourue, _Alpha, _Beta, Acc, Acc).
maxEvalPlateaux([[_Plateau,_Case,_Type]|_L], _SigneJoueur, _SigneAdv, _Tour, _TourMax, _Prof, _ProfParcourue, Alpha, Beta, Acc, Acc) :-
        Alpha >= Beta,
        !.
maxEvalPlateaux([[Plateau,Case,Type]|L], SigneJoueur, SigneAdv, Tour, TourMax, 0, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        evalue([Plateau,Case,Type], SigneJoueur, SigneAdv, ProfParcourue, Eval),
        min_member(Beta2, [Beta,Eval]),
        maxEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, 0, ProfParcourue, Alpha, Beta2, [[[Plateau,Case,Type],Eval]|Acc], CoupsEvalues),
        !.
maxEvalPlateaux([[Plateau,Case,g]|L], SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        evalue([Plateau,Case,g], SigneJoueur, SigneAdv, ProfParcourue, Eval),
        min_member(Beta2, [Beta,Eval]),
        maxEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta2, [[[Plateau,Case,g],Eval]|Acc], CoupsEvalues),
        !.
maxEvalPlateaux([[Plateau,Case,p]|L], SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        evalue([Plateau,Case,p], SigneJoueur, SigneAdv, ProfParcourue, Eval),
        min_member(Beta2, [Beta,Eval]),
        maxEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta2, [[[Plateau,Case,p],Eval]|Acc], CoupsEvalues),
        !.

maxEvalPlateaux([[Plateau,Case,Type]|L], SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta, Acc, CoupsEvalues) :-
        plateauxSuivants(Plateau, SigneJoueur, SigneJoueur, SigneAdv, Tour, TourMax, R),
        Prof2 is Prof - 1,
        ProfParcourue2 is ProfParcourue + 1,
        minEvalPlateaux(R, SigneJoueur, SigneAdv, Tour, TourMax, Prof2, ProfParcourue2, Alpha, Beta, [], CoupsMinEvalues),
        maxCoups(CoupsMinEvalues, [_,-1000], [_MeillCoup,MeillEval]),
        min_member(Beta2, [Beta,MeillEval]),
        maxEvalPlateaux(L, SigneJoueur, SigneAdv, Tour, TourMax, Prof, ProfParcourue, Alpha, Beta2, [[[Plateau,Case,Type],MeillEval]|Acc], CoupsEvalues).

alphaBeta(Plateau, SigneJoueur, SigneAdv, Tour, TourMax, Prof, MeilleurCoup) :-
        plateauxSuivants(Plateau, SigneJoueur, SigneJoueur, SigneAdv, Tour, TourMax, R),
        Prof2 is Prof - 1,
        minEvalPlateaux(R, SigneJoueur, SigneAdv, Tour, TourMax, Prof2, 1, -10000, 10000, [], CoupsEvalues),
        maxCoups(CoupsEvalues, [_,-1000], [MeilleurCoup,_]).

                     
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%       PREDICAT DE LANCEMENT
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

jouerCoup([A,B,C,D,E,F,G,H,I],SigneSousPlateau, SigneJoueur, SigneAdv, Tour, TourMax, Case, TypeCoup, NPlateau) :-
         ( SigneSousPlateau = a -> Prof is 3,
                                   alphaBeta(A, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = b -> Prof is 3,
                                   alphaBeta(B, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = c -> Prof is 3,
                                   alphaBeta(C, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = d -> Prof is 3,
                                   alphaBeta(D, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = e -> Prof is 3,
                                   alphaBeta(E, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = f -> Prof is 3,
                                   alphaBeta(F, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = g -> Prof is 3,
                                   alphaBeta(G, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = h -> Prof is 3,
                                   alphaBeta(H, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !;
          SigneSousPlateau = i -> Prof is 3,
                                   alphaBeta(I, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
                                   write(NPlateau),
                                   !
        ).
lancement(Plateau,SigneSousPlateau, SigneJoueur, SigneAdv, Tour, TourMax, Case, TypeCoup, NPlateau) :-
        
        jouerCoup(Plateau,SigneSousPlateau, SigneJoueur, SigneAdv, Tour, TourMax, Case, TypeCoup, NPlateau).

%        lancement(Plateau, SigneJoueur, SigneAdv, Tour, TourMax, Case, TypeCoup, NPlateau) :-
%                          Prof is 2,
%                                   alphaBeta(Plateau, SigneJoueur, SigneAdv, Tour, TourMax, Prof, [NPlateau,Case,TypeCoup]),
%                                   write(NPlateau),
%                                   !.
%lancement([[x,o,v,o,o,x,o,x,o],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v],[v,v,v,v,v,v,v,v,v]],a, x, o, 9, 9, Case, TypeCoup, NPlateau).

