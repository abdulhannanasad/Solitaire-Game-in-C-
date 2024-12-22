#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
class List
{
private:
	class Node
	{
	public:
		Node* next;
		Node* previous;
		T data;

		Node()
		{
			next = nullptr;
			previous = nullptr;
		}

		Node(T d, Node* n = nullptr, Node* p = nullptr)
		{
			data = d;
			next = n;
			previous = p;
		}
	};

	Node* head;
	Node* tail;
	int size;
public:
	class Iterator
	{
		friend class List;
		Node* curr;

		Iterator(Node* p)
		{
			curr = p;
		}

	public:
		Iterator()
		{
			curr = nullptr;
		}

		T& operator* ()
		{
			return curr->data;
		}

		Iterator operator++(int)
		{
			Iterator temp = *this;
			curr = curr->next;
			return temp;
		}

		Iterator& operator++()
		{
			curr = curr->next;
			return *this;
		}

		Iterator& operator--()
		{
			curr = curr->previous;
			return *this;
		}

		Iterator& operator--(int)
		{
			Iterator temp = *this;
			curr = curr->previous;
			return temp;
		}

		bool operator==(const Iterator& rhs) const
		{
			return curr == rhs.curr;
		}

		bool operator!=(const Iterator& rhs) const
		{
			return curr != rhs.curr;
		}

	};

	List()
	{
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->previous = head;
		size = 0;
	}

	Iterator begin() const
	{
		Iterator it(head->next);
		return it;
	}

	Iterator end() const
	{
		Iterator temp(tail);
		return temp;
	}

	bool isEmptyList()
	{
		if (head->next == tail)
		{
			return true;
		}
		else
			return false;
	}

	void InsertAtBeginning(T d)
	{
		Node* temp = new Node(d, head->next, head);
		head->next->previous = temp;
		head->next = temp;
		size++;
	}

	void InsertAtEnd(T d)
	{
		Node* temp = new Node(d, tail, tail->previous);
		tail->previous->next = temp;
		tail->previous = temp;
		size++;
	}

	void DeleteFromBeginning()
	{
		if (head == nullptr)
		{
			return;
		}

		Node* temp = head->next;

		if (temp == tail)
		{
			delete temp;
			head->next = tail;
			tail->previous = head;
			return;
		}

		head->next = temp->next;
		if (temp->next != nullptr)
		{
			temp->next->previous = head;
		}

		delete temp;
	}

	void deleteCard()
	{
		Node* temp = tail->previous;
		temp->previous->next = tail;
		tail->previous = temp->previous;
	}

	void display()
	{
		Iterator it;
		for (it = begin(); it != end(); it++)
		{
			cout << *it << " " << endl;
		}
	}

	bool pop(T& data)
	{
		if (isEmptyList())
		{
			return false;
		}

		Node* temp = tail->previous;
		data = temp->data;
		tail->previous = temp->previous;
		if (temp->previous != nullptr)
		{
			temp->previous->next = tail;
		}

		delete temp;
		size--;
		return true;
	}

	T getHead()
	{
		if (!isEmptyList())
		{
			return head->next->data;
		}

		throw runtime_error("List is empty");
	}

	T getTail()
	{
		if (!isEmptyList())
		{
			return tail->previous->data;
		}
		return nullptr;
	}

	void add(T d)
	{
		if (d != nullptr)
		{
			InsertAtEnd(d);
		}

		else
		{
			cout << "\aError: Cannot add an empty card" << endl;
		}
	}

	void removeTarget(T d)
	{
		Node* current = head->next;
		while (current != tail && current->data != d)
		{
			current = current->next;
		}

		if (current != tail)
		{
			current->previous->next = current->next;
			current->next->previous = current->previous;
			delete current;
			size--;
		}
	}

	bool subList(Iterator sourceStart, Iterator sourceEnd, Iterator dest)
	{
		if (sourceStart.curr != nullptr && dest.curr != nullptr)
		{
			Node* startNode = sourceStart.curr;
			Node* endNode = sourceEnd.curr;

			if (startNode->previous != nullptr)
			{
				startNode->previous->next = endNode;
			}

			if (endNode != nullptr)
			{
				endNode->previous = startNode->previous;
			}

			Node* destNode = dest.curr;
			if (destNode != nullptr)
			{
				startNode->previous = destNode;
				startNode->next = destNode->next;
				if (destNode->next != nullptr)
				{
					destNode->next->previous = startNode;
				}
				destNode->next = startNode;
			}

			else
			{
				startNode->previous = nullptr;
				startNode->next = nullptr;
			}

			return true;
		}
		return false;
	}

	int getSize()
	{
		return size;
	}

};

template <class T>
class Stack
{
private:
	List<T> s;
	int size;
public:
	Stack()
	{
		size = 0;
	}

	void push(T d)
	{
		s.InsertAtBeginning(d);
		size++;
	}

	bool pop(T& card)
	{
		if (!isEmpty())
		{
			card = s.getHead();
			s.DeleteFromBeginning();
			size--;
			return true;
		}

		else
			return false;
	}

	bool top(T& card)
	{
		if (!isEmpty())
		{
			card = s.getHead();
			return true;
		}

		else
			return false;
	}

	bool isEmpty()
	{
		if (s.isEmptyList())
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	int getSize()
	{
		return size;
	}
};

class Card
{
public:
	char suit;
	char rank;
	bool FaceUp;

	Card(char s, char r)
	{
		suit = s;
		rank = r;
		FaceUp = true;
	}

	void turnFaceUp()
	{
		if (FaceUp);
		FaceUp = !FaceUp;
	}

	int getRank()
	{
		if (rank == 'A')
		{
			return 1;
		}
		else if (rank == 'J')
		{
			return 11;
		}
		else if (rank == 'Q')
		{
			return 12;
		}
		else if (rank == 'K')
		{
			return 13;
		}
		else if (rank == 'T')
		{
			return 10;
		}
		else if (rank >= '2' && rank <= '9')
		{
			return rank - '0';
		}

		return -1;
	}

	bool isFaceUp()
	{
		return FaceUp;
	}

	void SetFaceUp()
	{
		FaceUp = true;
	}

	bool isRed() const
	{
		return (suit == 'H' || suit == 'D'); // Hearts or Diamonds
	}

	bool isBlack() const
	{
		return (suit == 'S' || suit == 'C'); // Spades or Clubs
	}

	void displayCard()
	{
		if (FaceUp)
		{
			if (rank == 'A')
			{
				cout << "A";
			}
			else if (rank == 'J')
			{
				cout << "J";
			}
			else if (rank == 'Q')
			{
				cout << "Q";
			}
			else if (rank == 'K')
			{
				cout << "K";
			}
			else if (rank == 'T')
			{
				cout << "10";
			}
			else
			{
				cout << rank;
			}

			cout << " of " << suit;
		}

		else
		{
			cout << "[ ]";
		}
	}

	friend ostream& operator<<(ostream& cout, Card* card)
	{
		if (card->isFaceUp())
		{
			if (card->rank == 'T')
			{
				cout << "10" << card->suit;
			}

			else
			{
				cout << card->rank << " of " << card->suit;
			}
		}

		else
		{
			cout << "[ X ]";
		}
		return cout;
	}

};

class Command
{
public:
	int numOfCards;
	int sourceTableau;
	int destTableau;
	int src;
	int dest;

	Command() {}

	Command(int num, int dt, int st, int s, int d)
	{
		numOfCards = num;
		sourceTableau = st;
		destTableau = dt;
		src = s;
		dest = d;
	}
};

class Game
{
	Card** deck;
	int deckSize = 52;
	Stack<Card*>stock;
	Stack<Card*>foundation[4];
	List<Card*>tableau[7];
	Stack<Card*>waste;
	
public:
	Stack<Command>undo;
	Game()
	{
		deck = nullptr;
		NewGame();
		deckShuffle();
		initialiseCards();
	
	}

	void NewGame()
	{
		deck = new Card * [deckSize];
		const int suitSize = 4;
		const int cardSize = 13;
		const char suits[] = { 'H', 'D', 'C', 'S' };  // Hearts, Diamonds, Clubs, Spades
		const char values[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
		int index = 0;
		for (int i = 0; i < suitSize; i++)
		{
			for (int j = 0; j < cardSize; j++)
			{
				deck[index] = new Card(suits[i], values[j]);
				deck[index]->turnFaceUp();
				index++;
			}
		}
	}

	void deckShuffle()
	{
		srand(static_cast<unsigned>(time(0)));
		for (int i = deckSize - 1; i > 0; i--)
		{
			int j = rand() % (i + 1);
			swap(deck[i], deck[j]);
		}
	}

	void initialiseCards()
	{
		int index = 0;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				Card* card = deck[index++];
				card->FaceUp = (j == i);
				tableau[i].InsertAtEnd(card);
			}
		}

		while (index < deckSize)
		{
			stock.push(deck[index++]);
		}
	}

	void StockToWaste()
	{
		Card* card = nullptr;
		bool flag = stock.pop(card);
		if (flag)
		{
			card->FaceUp = true;
			waste.push(card);
		}
	}

	void WasteToStock()
	{
		if (stock.isEmpty())
		{
			Card* card = nullptr;

			while (waste.pop(card))
			{
				if (card != nullptr)
				{
					card->FaceUp = false;
					stock.push(card);
				}
			}
		}
	}

	bool canMoveToFoundation(Card* c, int index)
	{
		Card* top = nullptr;
		bool isFoundationEmpty = foundation[index].top(top);
		if (!isFoundationEmpty)
		{
			return c->rank == 'A';
		}

		else
		{
			return (c->suit == top->suit && c->getRank() == top->getRank() + 1);
		}
	}

	bool WasteToFoundation(int index)
	{
		if (waste.isEmpty())
		{
			return false;
		}

		Card* card = nullptr;
		bool flag = waste.top(card);

		if (flag && canMoveToFoundation(card, index))
		{
			bool removeCard = waste.pop(card);
			if (removeCard)
			{
				foundation[index].push(card);
				return true;
			}
		}
		return false;
	}

	bool canMoveToTableau(Card* card, int index)
	{
		Card* tableauCard = tableau[index].getTail();
		if (tableauCard == nullptr)
		{
			return card->rank == 'K';
		}

		if ((tableauCard->isBlack() != card->isBlack() && tableauCard->getRank() == card->getRank() + 1) || (tableauCard->isRed() != card->isRed() && tableauCard->getRank() == card->getRank() + 1))
		{
			return true;
		}
		return false;
	}

	bool TableauToFoundation(int tableauIndex, int foundationIndex)
	{
		if (tableau[tableauIndex].isEmptyList())
			return false;

		Card* card = tableau[tableauIndex].getTail();
		if (canMoveToFoundation(card, foundationIndex))
		{
			tableau[tableauIndex].removeTarget(card);
			if (tableau[tableauIndex].getSize() > 0)
			{
				tableau[tableauIndex].getTail()->SetFaceUp();
			}
			foundation[foundationIndex].push(card);
			return true;
		}
		return false;
	}

	bool moveBetweenTableaus(int source, int dest)
	{
		if (tableau[source].isEmptyList())
		{
			return false;
		}

		Card* card = tableau[source].getTail();
		if (card != nullptr && canMoveToTableau(card, dest))
		{
			tableau[source].removeTarget(card);
			tableau[dest].add(card);
			tableau[source].getTail()->SetFaceUp();
			return true;
		}
		return false;
	}

	bool WasteToTableau(int col)
	{
		Card* c = nullptr;
		bool topCard = waste.top(c);
		Card* column = tableau[col].getTail();
		if (tableau[col].isEmptyList() && c->rank != 'K')
		{
			return false;
		}

		if (topCard && column != nullptr)
		{
			if ((c->isBlack() != column->isBlack() && c->getRank() < column->getRank()) || (c->isRed() != column->isRed() && c->getRank() < column->getRank()))
			{
				bool flag = waste.pop(c);
				tableau[col].add(c);
				return true;
			}
		}

		else
		{
			return false;
		}
	}

	bool MoveCards(int src, int dest, int numofCards)
	{
		if (tableau[src].isEmptyList() || numofCards <= 0)
		{
			return false;
		}

		if (tableau[src].getSize() >= numofCards)
		{
			List<Card*>::Iterator sourceEnd = tableau[src].end();
			List<Card*>::Iterator sourceStart = sourceEnd;

			for (int i = 0; i < numofCards; i++)
			{
				if (sourceStart != tableau[src].begin())
				{
					--sourceStart;
				}
			}

			for (List<Card*>::Iterator it = sourceStart; it != sourceEnd; ++it)
			{
				if (!(*it)->isFaceUp())
				{
					return false;
				}
			}

			Card* card = *sourceStart;
			if (canMoveToTableau(card, dest))
			{
				tableau[dest].subList(sourceStart, sourceEnd, tableau[dest].end());
				return true;
			}
		}
		return false;
	}


	void CommandParse(Command& cmd)
	{
		bool flag = false;
		if (cmd.src == 0 && cmd.dest == 0)
		{
			flag = moveBetweenTableaus(cmd.sourceTableau, cmd.destTableau);
			if (cmd.numOfCards > 1)
			{
				flag = MoveCards(cmd.sourceTableau, cmd.destTableau, cmd.numOfCards);
			}
		}

		if (cmd.src == 1 && cmd.dest == 2)
		{
			StockToWaste();
		}

		if (cmd.src == 2 && cmd.dest == 1)
		{
			WasteToStock();
		}

		if (cmd.src == 2 && cmd.dest == 0)
		{
			flag = WasteToTableau(cmd.destTableau);
		}

		if (cmd.src == 2 && cmd.dest == 3)
		{
			flag = WasteToFoundation(cmd.destTableau);
		}

		if (cmd.src == 0 && cmd.dest == 3)
		{
			flag = TableauToFoundation(cmd.sourceTableau, cmd.destTableau);
		}

		if (flag)
		{
			undo.push(cmd);
		}
	}

	void UndoLastCommand()
	{
		Command cmd;
		if (!undo.isEmpty())
		{
			bool flag = undo.pop(cmd);
			if (flag)
			{
				cout << "Undoing command" << endl;
				reverseCommand(cmd);
			}
		}
	}

	void reverseCommand(Command& cmd)
	{
		if (cmd.src == 0 && cmd.dest == 0)
		{
			// Reverse move between tableaus
			MoveCards(cmd.destTableau, cmd.sourceTableau, cmd.numOfCards);
		}

		if (cmd.src == 1 && cmd.dest == 2)
		{
			// Reverse move from stock to waste
			WasteToStock();
		}

		if (cmd.src == 2 && cmd.dest == 0)
		{
			// Reverse move from waste to tableau
			int index = cmd.destTableau;
			Card* card = nullptr;
			if (tableau[index].pop(card) && card != nullptr)
			{
				waste.push(card);
			}
		}

		if (cmd.src == 2 && cmd.dest == 3)
		{
			// Reverse move from waste to foundation
			int foundationIndex = cmd.destTableau;
			Card* card = nullptr;
			if (foundation[foundationIndex].pop(card) && card != nullptr)
			{
				waste.push(card);
			}
		}

		if (cmd.src == 0 && cmd.dest == 3)
		{
			// Reverse move from tableau to foundation
			int foundationIndex = cmd.destTableau;
			int tableauIndex = cmd.sourceTableau;
			Card* card = nullptr;
			if (foundation[foundationIndex].pop(card) && card != nullptr)
			{
				tableau[tableauIndex].add(card);
			}
		}

		if (cmd.src == 3 && cmd.dest == 0)
		{
			// Reverse move from foundation to tableau
			int foundationIndex = cmd.sourceTableau;
			int tableauIndex = cmd.destTableau;
			Card* card = nullptr;
			if (tableau[tableauIndex].pop(card) && card != nullptr)
			{
				foundation[foundationIndex].push(card);
			}
		}
	}

	void displayGame()
	{
		// Stock and Waste
		cout << "\n";
		cout << "Stock [ ";
		if (stock.isEmpty())
		{
			cout << "Empty";
		}

		else
		{
			cout << stock.getSize() << " cards";
		}
		cout << " ]    Waste [ ";

		if (waste.isEmpty())
		{
			cout << "Empty";
		}

		else
		{
			Card* card = nullptr;
			if (waste.top(card) && card != nullptr)
			{
				card->displayCard();
				cout << " (" << waste.getSize() << " cards)";
			}

			else
			{
				cout << "Empty";
			}
		}
		cout << " ]\n\n";

		// Foundations
		cout << "Foundations:\n";
		for (int i = 0; i < 4; i++)
		{
			cout << "    F" << i + 1 << "[ ";
			if (foundation[i].isEmpty())
			{
				cout << "Empty";
			}

			else
			{
				Card* card = nullptr;
				if (foundation[i].top(card) && card != nullptr)
				{
					card->displayCard();
					cout << " (" << foundation[i].getSize() << " cards)";
				}
			}
			cout << " ]";
			if (i < 3) cout << "    ";
		}
		cout << "\n\n";

		int maxHeight = 0;
		for (int i = 0; i < 7; i++)
		{
			maxHeight = max(maxHeight, tableau[i].getSize());
		}

		cout << "Tableaus:\n";
		cout << "     ";
		for (int i = 0; i < 7; i++)
		{
			cout << "  T" << (i + 1) << "          ";
		}
		cout << "\n     ";
		for (int i = 0; i < 7; i++)
		{
			cout << "------------ ";
		}
		cout << endl;

		for (int row = 0; row < maxHeight; row++)
		{
			cout << "     ";
			for (int col = 0; col < 7; col++)
			{
				if (row < tableau[col].getSize())
				{
					auto it = tableau[col].begin();
					for (int i = 0; i < row; i++) ++it;
					Card* card = *it;
					card->displayCard();

					int cardLength = card->FaceUp ? ((card->rank == 'T') ? 9 : 8) : 3;
					cout << string(12 - cardLength, ' ');
				}

				else
				{
					cout << "            ";
				}
				cout << "  ";
			}
			cout << endl;
		}

		cout << "\nCards:  ";
		for (int i = 0; i < 7; i++)
		{
			cout << "(" << tableau[i].getSize() << ")";
			cout << "          ";
		}
		cout << "\n" << endl;
	}


	bool checkGameWon()
	{
		for (int i = 0; i < 4; i++)
		{
			if (foundation[i].getSize() != 13)
				return false;
		}

		return true;
	}

	~Game()
	{
		for (int i = 0; i < deckSize; i++)
		{
			delete[] deck[i];
		}

		delete[] deck;
	}
};

int main()
{
	string invalid="0";
	Game solitaire;
	solitaire.displayGame();

	char input;
	int numOfCards, source, destination, from, to;

	cout << "\nFor stock move, press 's'\n"
		<< "For undo, press 'z'\n"
		<< "To quit, press 'q'\n"
		<< "For other moves, press 'm'\n" << endl;

	while (!solitaire.checkGameWon())
	{
		cout << "Enter your choice: ";
		cin >> input;

		if (input == 's')
		{
			Command cmd(1, 0, 0, 1, 2);
			solitaire.CommandParse(cmd);
		}
		else if (input == 'z')
		{
			cout << "Undoing..." << endl;
			solitaire.UndoLastCommand();
		}
		else if (input == 'q')
		{
			cout << "Quitting the game..." << endl;
			return 0;
		}
		else if (input == 'm')
		{
			cout << "Enter number of cards: ";
			cin >> numOfCards;

			cout << "Enter source (0 for tableau, 1 for stock, 2 for waste): ";
			cin >> source;

			cout << "Enter destination (0 for tableau, 2 for waste, 3 for foundation): ";
			cin >> destination;

			cout << "Enter FROM where you want to move (tableau index if applicable): ";
			cin >> from;

			cout << "Enter where you want TO move (tableau index if applicable): ";
			cin >> to;

			Command cmd(numOfCards, to, from, source, destination);
			solitaire.CommandParse(cmd);
		}

		else
		{
			 invalid= "Invalid input! Please enter 's' for stock move, 'z' for undo, 'q' for quit, or 'm' for move." ;
		}

		system("cls");


		solitaire.displayGame();
		if (invalid != "0")
		{
			cout<<endl <<invalid<<endl;
			invalid = "0";
		}
		cout << "\nFor stock move, press 's'\n"
			<< "For undo, press 'z'\n"
			<< "To quit, press 'q'\n"
			<< "For other moves, press 'm'\n" << endl;
	}

	cout << "You won!" << endl;
	return 0;
}

