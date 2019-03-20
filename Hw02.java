
import java.util.Random;
import java.io.File;
import java.io.FileReader;
import java.util.Scanner;

// ja573625
// Jacob Rogers
// COP 3503, Spring 2019
// March-24-2019

// A program to take inputs from a text file to insert, delete, add, and search from a skiplist. 

public class Hw02{ 

	private Scanner x;
	int levelCount;

	private class Node{
		int data;
		Node left;
		Node right;
		Node up;
		Node down;
		
		private Node(int data) {
			this.data = data;
			left = null;
			right = null;
			up = null;
			down = null;
		}

	}

	public static Random unseededRandom = new Random(42); 
	public static Random seededRandom = new Random();

	// The root will be the bottom left.
	public static Node root;
	public Hw02() {
		this.root = null;
	}


	public static void main(String[] args) {
		
		String fileInName = null;
		boolean seed = false;

		if(args.length != 0){

			fileInName = args[0];

			if(args.length > 1){
				if(args[1].equals("r") || args[1].equals("R"))
					seed = true;
				else{
					System.out.println("Error: enter r or R to signify random seeding.");
					return;
				}
			}

			Hw02 skip_list = new Hw02();

			skip_list.openFile(fileInName);
			skip_list.readFile(seed, fileInName);
			skip_list.closeFile();
			skip_list.complexityIndicator();
				

		}

	}

	public void complexityIndicator(){
		System.err.println("ja573625;2.5;12");
		return;
	}

	public void openFile(String name){
		try{
			x = new Scanner(new File(name));
		}
		catch(Exception e){
			System.out.println("could not find file");
		}
	}

	public void closeFile(){
		x.close();
	}

	// Get the input from each line and call the corresponding methods.
	public void readFile(boolean seed, String fileInName){
		String operation = null;
		int data = 0, level = 0;

		System.out.println("For the input file named " + fileInName);
		if(seed == false)
			System.out.println("With the RNG unseeded,");
		else
			System.out.println("With the RNG seeded,");

		while(x.hasNext()){
			// Get the string portion of the input line.
			operation = x.next();

			// Deal with p and q seperatlety as they have no data following them.
			if(operation.equals("p") || operation.equals("q")){
				if(operation.equals("p"))
					printAll();
				
				else if(operation.equals("q"))
					break;
				
			}

			// If not p or q, get the int portion of the input line.
			else
				data = x.nextInt();
			
			// Call insert; will pass the data, seed setting, and the current # of levels in the skiplist.
			// Update the level #.
			if(operation.equals("i"))
				level = insert(data, seed, level);

			if(operation.equals("s"))
				search(data);

			if(operation.equals("d"))
				delete(data);

		}
	}

	public void printAll(){
		Node current = root, climber;
		
		System.out.println("the current Skip List is shown below: ");
		System.out.println("---infinity");

		if(root != null){
			// Move off of the -infinity nodes.
			current = current.right;
			climber = current;
			do {

				System.out.print(" " + current.data + "; ");

				while(climber.up != null){
					climber = climber.up;
					System.out.print(" " + climber.data + "; ");
				}
				
				current = current.right;
				climber = current;
				System.out.println();

			} while(current.right != null);
		}

		System.out.println("+++infinity\n---End of Skip List---");

		return;
	}

	public void delete(int data){
		Node current;

		if(root == null){
			System.out.println(data + " integer not found - delete not successful");
			return;
		}

		current = root;

		while(current.data < data){
			current = current.right;

			if(current.data > data){
				System.out.println(data + " integer not found - delete not successful");
				return;
			}

			else if(current.data == data){	
				
				do{
					current.right.left = current.left;
					current.left.right = current.right;
					current.right = null;
					current.left = null;

					if(current.up != null)
						current = current.up;
					else
						break;		
				} while (current != null);
				
				System.out.println(data + " deleted");
			}
		}
		return;
	}

	public void search(int data){
		Node current, climber;

		if(root == null){
			System.out.println(data + " NOT FOUND");
			return;
		}

		current = climber = root;

		while(current.up != null)
			current = current.up;

		while(current.data < data){
			//System.out.println("1");
			//System.out.println("current: " + current.data);

			current = current.right;
			//System.out.println("current: " + current.data);


			if(current.data == data){
				System.out.println(data + " found");
				return;
			}

			else if(current.data > data){
				//System.out.println("2");
				current = current.left;

				if(current.down == null){
					System.out.println(data + " NOT FOUND");
					return;
				}
				//System.out.println("3");
				current = current.down;
				//System.out.println("4");
			}
		}		
		return;
	}

	// Insert a node into the skiplist with the data.
	// Will return the updated number of levels in the skiplist.
	public int insert(int data, boolean seed, int level){
		int coinFlipLevel = -1, currentLevel = 1;
		String coinFlipResult = "Tails";
		Node newNode, current, above, climber, previousInsert = null;
		newNode = createNode(data);
		
		// If the skiplist is empty, create the bottom level.
		if(level == 0){
			initalizeLevel();
			level++;
		}

		current = root;
		climber = root;

		// Determine the number of heads flipped in a row for the level of the insertion.
		do{
			
			coinFlipResult = promote(seed);
			coinFlipLevel++;
		} while(coinFlipResult.equals("Heads")); 

		// Start at the root (level 1), traverse right until at the right spot, insert.
		// If needed, go up.
		while(current.data < data){
			current = current.right;

			if(current.data >= data){

				if(current.data != data){
					// Reset pointers on bottom level for insert.
					newNode.left = current.left;
					newNode.right = current;
					current.left.right = newNode;
					current.left = newNode;
					previousInsert = newNode;
				}
				
				else if(current.data == data)
					previousInsert = current;
				
				// If need to go up a level.
				while(currentLevel <= coinFlipLevel){
					
					// If the node was already inserted on the next level, continue to next iteration.
					if(previousInsert.up != null){
						climber = climber.up;
						previousInsert = previousInsert.up;
						currentLevel++;
						continue;
					}
							
					// If there is no level above, initalize one.
					if(climber.up == null){
						initalizeLevel();
						climber = climber.up;
						level++;
						currentLevel++;
					}

					// Otherwise, climb anyway to the next level.
					else{
						climber = climber.up;
						currentLevel++;
					}
					// Traverse right to the correct location on the next level up.
					current = climber;
					while(current.data < data){
						current = current.right;

						// Found location for insert. Connect the right and left pointers.
						if(current.data >= data){
								above = createNode(data);	

								// Connect the left and right pointers.	
								above.left = current.left;
								above.right = current;
								current.left.right = above;
								current.left = above;

								// Connect the up and down pointers.
								previousInsert.up = above;
								above.down = previousInsert;

								previousInsert = above;
						
						}
					
					}
				
				}
			}
		}
		return level;
	}

	public Node createNode(int data){
		Node newNode = new Node(data);
		return newNode;
	}

	// Initalize a new level with two nodes with data of -1 and 10,001.
	// -1 is less than the lower bound of data constrained by the project and 10,001 is above it
	// so they will act as positive and negitive infinity.
	// Assign the root to the bottom left.
	// Always initalizing the new level directly above the given node "current."
	public void initalizeLevel(){
		Node negInfNode = new Node(-1);
		Node posInfNode = new Node(10001);
		Node current = root;

		if(root == null){
			negInfNode.right = posInfNode;
			posInfNode.left = negInfNode;
			root = negInfNode;
			return;
		}

		// Climb until current.up == null.
		while(current.up != null)
			current = current.up;

		// Create the new level, set pointers.
		current.up = negInfNode;
		negInfNode.down = current;
		negInfNode.right = posInfNode;
		posInfNode.left = negInfNode;

		return;
	}

	// Returns Heads or Tails for a simulated coin flip.
	// If seed is false it will be set to 42, else random.
	public String promote(boolean seed){
		int randInt = 0, flip = 1;
  
        // Generate a random integer and mod by 2 to determine heads or tails for the insertion, seeding option.
		if(seed == true)
        	randInt = seededRandom.nextInt(); 
        else
        	randInt = unseededRandom.nextInt();

        flip = randInt % 2;

        if(flip == 1)
        	return "Heads";
        else
        	return "Tails";
	}
}