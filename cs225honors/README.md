# CS 225 New MP3: Snakes

For this assignment, you will get to test our one of our new MPs that uses SFML to create a snake game you can play on your keyboard. You will be completing a new version of MP3 so that you create a linked-list with different functionality, along with a game object that keeps track of your board. You may work on a partner if you wish, and this assignment is estimated to take two weeks to complete.
## Getting Started:

1. Click fork to create your own copy of the repo.
2. Once the repository is forked:
  * Click Members on the menu on the right hand side
  * Search for c-heeren and add Cinda as a Reporter
    (This allows me to have read-access to your files.)
    
## Cloning the CS225 Honors Repository

After you have forked your copy of the repo, you need to download it to your 
CS225honors working directory:

1. Open up your command line interface
2. Navigate to your cs225honors working directory
3. Run `git clone https://gitlab-beta.engr.illinois.edu/NETID/cs225honors.git`
    Make sure to replace NETID with your NetID
4. Run the following command to add a new remote:
`git remote add release https://gitlab-beta.engr.illinois.edu/cheeren/cs225honors.git`
    Your repo is now referred to as `master` and mine is `release`.
    
## Part 1: The Linked List

The first part of this MP is the complete the linked-list object we will need for part 2. It is a doubly linked list with a head pointer pointing to it's first node, and a tail pointer poiting to it's last node. However this linked-list has some different functionality than our current MP3's linked list.

### clear() and destructor
As in your current MP3, you must implement a clear function that will destroy your list, and a destructor that will utilized the clear function

### insertFront(T const & ndata)
As in your current MP3, this function should insert a node with ndata at the front of your list

### popBack()
This function should remove the last node of your list, and return what it was holding

### reverse()
This function should reverse your list.

### reverse( ListNode * & startPoint, ListNode * & endPoint )
This function should reverse a portion of your list.

### split()
Update your list to contain the nodes in the first (length/2) node of our list, and return a list containing the nodes in the remaining part of the list.

### mergeWith(List<T> & otherList)
Attach the otherList to the back of your list, and clear out your otherList. Your list and otherList may not share nodes.

## Part 2: The Game Object

We will now create a game object that is utilized by our main.cpp to store information about our snake game. Our object maintains a char array called grid which stores the data for every cell of our game. If a cell has '.', that space is empty. If a cell has 'R', that space is part of our red snake. If a cell has 'G', that space is part of our green snake. If a cell has 'r', that space is holding a red apple. If a cell has 'g', that space is holding a green apple. We have a red list to keep a track of the cell locations of our red snake, a green list to keep a track of the cell locations of our green snake, and a changes list to keep a track of what cell locations have changed during a user's turn. The integers headx and heady hold the x and y locations of the front of our active snake(red or green). The boolean redalive should keep track of which snake is active. The integer side is the width of our square grid.

Our game starts off with our red snake of size 1 into the top left corner, and a red apple in the center location of the grid. We can move our snake to run into the apple to increase it's size. After our snake grows to a length of 5, green apples may appear randomly. To pick up a green apple, the red snake splits itself into a dormant red half and a green active half. The green snake can pick up the red apple, and then run into the tail of the red snake to give the user control of the full red snake again.

### Game(int n)
This should contruct your game object, with your grid array having n*n characters. At this point, your red snake is in the corner of the grid and your red apple is in location ((n/2),(n/2)) of the grid. Your data structures should reflect this.

### copy(const Game & other)
This shoud copy another game object

### Game( const Game & other )
Copy constructor

### ~Game()
Destructor

### operator=( const Game & rhs )
Should set the current game object equal to rhs

### ~Game()
Should destroy any allocated memory of our game

### score()
Should return the length of the active snake(red or green)

### print()
This function prints out the game for you. This function has been completed for you and may be helpful in testing.

### nextApple()
This function is called when the user has grabbed an apple and another needs to be generated. You should generate a random integer, and if the location is unfilled you can place an apple there. If the red list has a size greater than 5, then you should flip a coin(have a 50% chance) to have this apple be green. The location of the apple should be added to the changes list.

### intersection(int problem)
This function handles the case when the snake controlled by the user(red or green) runs into itself at the integer location "problem". Our game is not over, but we must remove cells from the back of the snake until we have removed "problem" from our snake once. The locations in the game that have been removed from the snake become black in the grid, and must be added to the changes list.

### nextTile(int dir)
This function is called when the users have specified a direction to move the list in, and we need to update our head
0->User has pressed down arrow
1->User has pressed left arrow
2->User has pressed right arrow
3->User has pressed up arrow

This function should update headx and heady, and then return ((heady * side) + headx). Our snake will wrap around if the user walks off the edge of ourgrid.

### backtrack(int dir)
This function checks if we're in the situation of when we try to move the active snake(red or green) in a direction opposite to the way it's pointing (Moving up when it's pointing down).
0->User has pressed down arrow
1->User has pressed left arrow
2->User has pressed right arrow
3->User has pressed up arrow

If your snake only has one node it is not pointing in any direction. You should return true if this is the case, and false otherwise.

### move(int dir)
This function takes in an integer representing the user input, and updates our data structures based on it.
0->User has pressed down arrow
1->User has pressed left arrow
2->User has pressed right arrow
3->User has pressed up arrow
Otherwise->User has pressed spacebar

Any cell locations that change color must be added to the changes list if not done so by helper functions.
#### User movement(0-3)
When the user has pressed an arrow key, it should move the snake currently active(red or green). If we are backtracking, we should simply reverse our snake. Otherwise we should add a cell to the front of our snake and mark it in the grid as a part of our snake. If we have just hit the apple of the snake's color, we should generate a new apple. If we have hit an apple not of the snake's color, we should remove the end of our snake and mark that location in grid as empty, and generate a new apple. If our green snake has run into our red snake, we should make our red snake active again, remove cells from the end of the snake up to and including the part where the green snake touched it(and mark these locations as empty except for the green's head), merge the two snakes, and mark the formerly green cells as part of the red snake. If our active snake is running into an empty spot, we should remove the last spot of our snake and mark it as empty in the grid.

#### Split(Otherwise)
When the user has pressed any other key, they want to try to split the snake. If the active snake is red and it's size is greater than 5, we will make our green snake the output of a red split in half, reverse the green snake, mark the green snake's locations in the grid.

## Testing
If your run "make" you should have the executable mp3snake which will run on EWS after running run.sh. Otherwise your should be able to run mp3local on your computer if you have set up SFML. You can also write your own main.cpp and use the print function to check if your game object is updating the grid correctly.
