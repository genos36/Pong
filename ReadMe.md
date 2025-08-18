#PONG
semplice pong orizzontale
il focus del progetto era capire un po' il framework sfml

#utilità:
gestione basilare delle collisioni
basilare desing di un progetto di programmazione a oggetti

#avvisi:
bug da fixare probabili (oppure diventano delle feature)

#nota:
va avanti all'infinito

sfml        2.6             o successive

CMake       3.15            o successive
Conan       2.19            o successive

#workflow

i file bash dovrebbero gestire la maggior parte del lavoro

updateDependencies.sh           aggiorna le dipendenze, richiede conan attivo
    
build.sh                        lancia il processo di build

è possibile usare direttamente cmake e poi make 


