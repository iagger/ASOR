renice 12 -p $$
chrt -f -p 12 $$ 

gcc ej2.c -o ej2
./ej2
rm ej2

chrt -o -p 0 $$ 

# si se heredan los atributos de planificación