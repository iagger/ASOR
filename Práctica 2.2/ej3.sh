mkdir pruebas
cd pruebas/

echo "#este es un fichero de prueba que se muestra a si mismo
cat fichero1" >> fichero1 

echo "#este es un fichero de prueba que se muestra a si mismo
cat fichero2" >> fichero2 

chmod u+rw-xx,g+r-wx,o-w+xr fichero2
chmod 645 fichero1

ls -l

cd ..
sudo rm -R pruebas/