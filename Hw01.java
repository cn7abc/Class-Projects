import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Scanner;

// ja573625
// Jacob Rogers
// COP 3503, Spring 2019
// February-28-2019

public class Hw01 {
	
	private class Node{
		int data;
		Node leftChild;
		Node rightChild;
		
		private Node(int data) {
			this.data = data;
			leftChild = null;
			rightChild = null;
		}

	}
	
	public static Node root;
	Node result;
	
	public Hw01() {
		this.root = null;
	}

	public static void main(String[] args) {
		
		String fileInName = null;
		
		if(args.length != 0) {
			fileInName = args[0];
				
			Hw01 r = new Hw01();
			
			System.out.printf("%s contains:\n", fileInName);
			
			try {
				File file = new File(fileInName);
				FileReader filereader = new FileReader(file);
				BufferedReader bufferedReader = new BufferedReader(filereader);
				StringBuffer stringBuffer = new StringBuffer();
				String line;
				
				while((line = bufferedReader.readLine()) != null) {
					stringBuffer.append(line);
					if(!line.equals("q"))
						stringBuffer.append("\n");
				}
				filereader.close();
				System.out.println(stringBuffer.toString());
			}
			catch(Exception e) {
				System.out.println("File not found");
			}
			r.openFile(fileInName);
			r.readFile();
			r.closeFile();	
			r.complexityIndicator();
		}
	}
	
	public void complexityIndicator() {
		System.err.println("ja573625;5.0;24");
	}
	
	private Scanner x;
	public void openFile(String name) {
		try {
			x = new Scanner(new File(name));
		}
		catch(Exception e) {
			System.out.println("could not find file");
		}
	}
	

	public void readFile() {
		Node ans;
		String op;
		int num = 0;
		
		
		while(x.hasNext()) {
			op = x.next();
			
			if(op.equals("p")==false && op.equals("q")==false
					&&op.equals("d")==false &&op.equals("s")==false
					&&op.equals("i")==false) 
			{
				break;
			}
			
			if(op.equals("p") || op.equals("q")) {				
				// Call to print.
				if(op.equals("p")) {
					print(root);
					System.out.println();
				}
				// Quit.
				if(op.equals("q")) {
					break;
				}	
			}
			
			else
			{
				num = x.nextInt();
			}
			
			// Call to insert.
			if(op.equals("i")) {
				insert(num);
			}
			// Call to search.
			if(op.equals("s")) {
				ans = search(root, num);
				if(ans == null)
					System.out.printf("%d: NOT found\n", num);
				if(ans != null)
					System.out.printf("%d: found\n", ans.data);
				ans = null;
			}
			
			// Call to delete.
			if(op.equals("d")) {
				ans = search(root, num);
			    Tdelete(ans);
			}
			
		}	
		countChildren(root);
	}
	
	public void closeFile() {
		x.close();
	}
	
	public void insert(int Zdata) {
		
		
		Node newNode = new Node(Zdata);
		
		
		// If the tree is empty, add a root.
		if(root==null){
			
			root = newNode;
			return;
		}
		
		Node Yparent = null;
		Node Xwalker = root;
		
		while(Xwalker != null) {
			Yparent = Xwalker;

			
			if(Zdata < Xwalker.data) 
			{ 
				Xwalker = Xwalker.leftChild;
				if(Xwalker == null) 
				{
					Yparent.leftChild = newNode;
					return;
				}
			}
			else 
			{
				Xwalker = Xwalker.rightChild;	
				if(Xwalker == null) 
				{
					Yparent.rightChild = newNode;
					return;
				}
			}	
		}
	}
	
	public void printInOrder(Node root) {
		if(root != null) {	
			if(root.leftChild !=null) {
				printInOrder(root.leftChild);
			}
			
			System.out.print(" " + root.data);
			
			if(root.rightChild !=null) {
				printInOrder(root.rightChild);
			}
		}
	}
	
	public void print(Node root) {
		printInOrder(root);	
	}
	
	public Node search(Node root, int num) {
		if(root == null)
			return null;
		
		if(root.data == num)
			return root;
		
		if(num < root.data)
			return search(root.leftChild, num);
		
		else if (num > root.data)
			return search(root.rightChild, num);
			
		return null;
	}
	
	public void transplant(Node u,Node v) {
		Node Uparent;
		Uparent = findParent(root, u, u.data);
		
		if(Uparent == null) { 
			root = v;
			return;
		}
		Uparent = findParent(root, u, u.data);
		if(u == Uparent.leftChild) {
			Uparent.leftChild = v;
			return;
		}
		else {
			Uparent = findParent(root, u,u.data);
			Uparent.rightChild = v;
		}
		return;
	}
	
	public void Tdelete(Node z) {
		Node y, parent;
		// No nodes.
		if(z == null) {
			return;
		}
		// Right child, no left child.
		if(z.leftChild == null) {
			transplant(z, z.rightChild);
			//print(root);
		}
		// Left child, no right child.
		else if(z.rightChild == null) {
			transplant(z, z.leftChild);
		}
		else{
			 y = treeMin(z.rightChild);
			 parent = findParent(root, y, y.data);
			if(parent != z) {
				transplant(y, y.rightChild);
				y.rightChild = z.rightChild;
				parent = findParent(root, y.rightChild, y.rightChild.data);
				parent = y;
			}
			transplant(z, y);
			y.leftChild = z.leftChild;
			parent = findParent(root, y.leftChild, y.leftChild.data);
			parent = y;
		}
	}
	
	public Node findParent(Node x, Node target, int data) {
		Node parent = x;
		String lastDirection = null;
		if(target == root) {
			return null;
		}
		int i = 0;
		while(x != target) {
			if(x != null || data != x.data) {
				if(data < x.data) {
					if(i != 0) {
						if(lastDirection.equals("l"))
							parent = parent.leftChild;
						else
							parent = parent.rightChild;
					}
					x = x.leftChild;
					lastDirection = "l";
				}
				else if(data >= x.data){
					if(i != 0) {
						if(lastDirection.equals("l"))
							parent = parent.leftChild;
						else
							parent = parent.rightChild;
					}
					x = x.rightChild;
					lastDirection = "r";
				}	
			}
			i++;
		}
		return parent;
	}
	
	
	public Node treeMin(Node x){
		while (x.leftChild != null)
			x = x.leftChild;
		return x;
	}
	
	
	public int countNodes(Node root) {
		if(root == null)
			return 0;
		
		return 1 + countNodes(root.leftChild) + countNodes(root.rightChild);
	}
	
	public int countDepth(Node root, int d) {
		if(root == null)
			return d - 1;
		
		return Math.max(countDepth(root.leftChild, d + 1),countDepth(root.rightChild, d + 1)); 
	}
	
	public void countChildren(Node root) {
		int right, left, leftC, rightC;
		
		left = countNodes(root.leftChild);
	    right = countNodes(root.rightChild);
				
		leftC = countDepth(root.leftChild, 1);	
		rightC = countDepth(root.rightChild, 1);
	
		System.out.printf("left children:%11d\n", left);
		System.out.printf("left depth:%14d\n", leftC);
		System.out.printf("right children:%10d\n", right);
		System.out.printf("right depth:%13d\n", rightC);
	}
}


