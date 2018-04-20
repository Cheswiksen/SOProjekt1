#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <mutex>

std::mutex mu;


void changePos(int &direction, int &x, int &y, bool &licznik)
{


	if(licznik == true)
	{
		if(direction == 1)
        	{
			direction = 5;
			licznik = false;
		}
	        else if(direction == 2)
	        {
			direction = 6;
			licznik = false;
	        }
	        else if(direction == 3)
	        {
	                direction = 7;
			licznik = false;
	        }
	        else if(direction == 4)
	        {
	                direction = 8;
			licznik = false;
	        }
	        else if(direction == 5)
	        {
	                direction = 1;
			licznik = false;
	        }
	        else if(direction == 6)
	        {
	                direction = 2;
			licznik = false;
	        }
	        else if(direction == 7)
	        {
	                direction = 3;
			licznik = false;
	        }
	        else if(direction == 8)
	        {
			direction = 4;
			licznik = false;
	        }
	
	}

	if(direction == 1)
        {
                x--;
        }
        if(direction == 2)
        {
                x--;
                y++;
        }
        if(direction == 3)
        {
                y++;
        }
        if(direction == 4)
        {
                x++;
                y++;
        }
        if(direction == 5)
        {
                x++;
        }
        if(direction == 6)
        {
                x++;
                y--;
        }
        if(direction == 7)
        {
                y--;
        }
        if(direction == 8)
        {
                x--;
                y--;
        }

}

void ball(int direction, int iter, int speed)
{
	bool licznik = false; 
	move(iter, 30);
	//mu.lock();
	printw("%d.%x",iter,std::this_thread::get_id());
	//mu.unlock();
	int x, y;
	x = y = 7;
	for(int i=0;i<64;i++)
        {
	
	       if(i==0)
	       {
		move(x, y);
		mu.lock();
                printw("*");
		refresh();
		mu.unlock();
		
	       }
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		move(x, y);
		mu.lock();
		printw(" ");
		refresh();
		mu.unlock();
		if(x == 14 || y == 14 || x ==  0 || y == 0)
		{
			licznik = true;
			//move(30,30);
			//printw("true   %d,%d", x, y);
		}
		//move(0,0);
		//printw("x=%d y=%d",x,y);
		changePos(direction, x, y, licznik); 
		move(x, y);
		mu.lock();
        	printw("*");
		refresh();
               	mu.unlock();
		

	}
	move(x, y);
	mu.lock();
        printw(" ");
	refresh();
	mu.unlock();
	move(iter, 30);
	printw("                           ");
	refresh();
}




int main()
{

	initscr();
	curs_set(0);
	srand (time(NULL));
	int v, Time, speed;
	
	static const int A = 20;
	std::thread T[A];
	for(int i=0; i<A; i++)
	{
		speed = rand() % 200 + 50;
		Time = rand() % 1000 + 100;	
		v = rand() % 8 + 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(Time));
		T[i] = std::thread(ball, v, i, speed);
	}
	for(int i=0; i<A; i++)
	{
		T[i].join();
	}

	refresh();
	

	getch();
	endwin();




	return 0;
}
