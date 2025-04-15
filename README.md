Comment utiliser git :



1- Relier git hub et git :
git config --global user.name "pseudo a mettre ici"
git config --global user.email email a mettre ici

2- Copier le code present sur git hub vers son pc :
git clone https://github.com/Alex0xB/Allegro-Ing-1
cd 'chemin d'acces au fichier'

3- Comment sauvegarder son code et l'envoyer :
A) git add .
B) git commit -m "Message du commit modifiable"  //Jusque la on fait une copie de notre code en local
C) git push origin master (ou main )//On envoi le code au git hub (Si probleme avec le mot main le remplacer par master)

4- Recuperer des fichiers :
git pull origin master (mettre main si ca ne marche pas)
