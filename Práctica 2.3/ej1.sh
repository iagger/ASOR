chrt -p $$
echo 
nice

renice 5 -p $$

chrt -p $$
echo 
nice

sudo renice 0 -p $$