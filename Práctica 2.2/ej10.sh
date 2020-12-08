mkdir ej10dir

echo "
Primer punto
-----------------------"
ln -s ej10dir ej10dirSim
ln -s ej10.sh ej10sim.sh  

ls -i | grep "ej10"

rm ej10sim.sh
rm ej10dirSim

echo "
Segundo punto
-----------------------"
ln ej10dir ej10dirRig
ln ej10.sh ej10rig.sh  

stat -t ej10.sh
stat -t ej10rig.sh

rm ej10rig.sh
#rm -R ej10dirRig

rm -R ej10dir

# Tercer punto
# Si se elimina un enlace rígido, se decrementará el número de enlaces del inodo correspondiente
# Si se elimina un enlace simbólico, no ocurre nada con el fichero original
# Si se elimina el fichero original, se decrementará el numero de enlaces por no que no afectaría a un enlace rígido, en cambio, si tuviera un enlace simbólico éste quedaría roto 