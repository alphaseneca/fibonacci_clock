# fibonacci_clock

A unique clock that uses the Fibonacci sequence to display time with colored squares, combining math and art in an innovative timekeeping design.

## Working

It works by lighing up a segment of the matrix based on the time in the Fibonacci sequence. If the time is 6:42 it will light up the segment **1** and **5** to **RED** which will add to give the hour 6. And for minutes it will light up the segment **3** and **5** to **BLUE** which will add to **8*5** equals to **40** minutes. And since the segment **5** are lit by both the hour and minutes it will change the colour to **GREEN** to show the overlap in the both hour and minutes. 

> The segment can only represent between **1 - 12** and to represent the minutes we are multiplying it by 5.
> Since the increments are in every 5 minutes thus the time can be between **40 - 45** Minutes.

![fibonacci_clock](images/fibonacci_clock_working.jpg)

Working Image:
![fibonacci_clock](images/Image1.jpg)
