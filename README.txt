README



Ez a program egy baktériumtelep quorum sensing működésének ágens alapú modelljét valósítja meg. Minden egyes kísérletet egy .xml paraméter fájlban lehet leírni. Ezen fájl alapján szükséges először a baktériumtörzseket leíró kód generálása és kiegészítése, amikkel ezután futtaható a szimuláció.

A különböző törzsekhez tartozó baktériumok viselkedését manuálisan szükséges megírni. A saját kísérleteimben használt két törzset leíró osztályok megtalálhatóak a /User mappában, így szimuláció futtatásához elegendő a következő sorozat 3. lépését elvégezni.




A program fordításához és futtatásához Qt 5 vagy későbbi verzió szükséges.

1. A fájlgenerálás menete a paraméterek alapján parancssorból, forráskódból kiindulva:
	1/1.	make distclean
	1/2.	qmake
	1/3.	make
	1/4.	./generate

	A parancsokat a /Params mappából kell kiadni.


2. A generált fájlokat át kell másolni a /User mappába.


3. Szimuláció futtatása a generált fájlokkal, forráskódból kiindulva:
	3/1.	make distclean
	3/2.	qmake
	3/3.	make
	3/4.	./world

	A parancsokat a /Gui mappából kell kiadni.




Az eddigi paraméterfájlok a /Gui/parameters mappában találhatóak. Új kísérletet itt található új .xml fájl használatával lehet végrehajtani.

Ha ebben az új fájlban a paraméterek száma, elnevezése és rendje nem változik, hanem csupán az értékük, akkor nem szükséges új osztályokat generálni. A kísérlet végrehajtható az új fájl elérési útvonalának megadásával a következő módon:

	./world ./parameters/params_k.xml


Amennyiben a baktériumok viselkedésén is változtatni szeretne (új jelet, új szabályt implementálni), a megfelelő .xml fájl létrehozása után a teljes fenti sorozat végrehajtása szükséges.

A modell és implementálásának részletesebb a leírása a szakdolgozatban található.




