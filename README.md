# philo

Rules :
N philosophers are around one table (N is defined on the command line). • Each philosopher has one rice bowl in front of him. • There is a chopstick at the left of each bowl. • A philosopher can only use a chopstick if it is at the left or at the right of his bowl. • A philosopher goes through three steps : ◦ Eats with two chopsticks. One left and one right. ◦ Rests, does not use any chopstick, even if one is available. ◦ Thinks, uses one and only one chopstick.
A philosopher that thinks must eat before resting. In order to get his energy back, obviously. • After resting, a philosopher can either eat, or think. • A chopstick cannot be used by two philosophers at the same time, for hygienic reasons, they said.

make

LD_LIBRARY_PATH=/home/username/libriceferee.so:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/home/username/libriceferee.so:$LD_LIBRARY_PATH

./philo -p nb -e nb

◦ -p followed by the number of philosophers. ◦ -e followed by the max eat occurence at which the program exits when one philosopher reaches it.
