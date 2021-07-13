# Simulated-Annealing-for-Projectile-Inclination
A project for an AI course I took in Spring 2019.

- There is an AI whose goal it is to hit a target with a projectile. 

- The user determines the distance of the projectile target and the height and distance of a wall between the initial position and the target position.

- The AI uses rudimentary simulated annealing to determine an angle that lands the projectile acceptably close to the target. Although this is something easily computable, it was neat to demonstrate how simulated annealing can help overcome local minima in the error-space.

- The physics are mostly realistic, taking place in a vacuum, and the initial velocity of the projectile is a constant.

- Iterations are plotted via gnuplot. Each plot automatically opens, and they are all saved to a "plots" directory.

![image](https://user-images.githubusercontent.com/6509842/125379086-e34efb80-e35d-11eb-83c0-6c51b7f8b988.png)

Here's an example solution where the target was 70m away and the wall was 30m high at a distance of 40m. Note that the default error tolerance is 0.5m.

![image](https://user-images.githubusercontent.com/6509842/125379227-24471000-e35e-11eb-930d-e0c5da960a70.png)

### Necessary software ###
- Gnuplot

- Boost libraries

### Shell scripts ###
- compile.sh compiles the project with the necessary flags.

- killGnuplot.sh kills all gnuplot processes that are currently running.

- rmGnuplot.sh removes the saved plots.
