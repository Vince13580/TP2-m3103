#include <iostream>

using namespace std;

//Exo1

template  <typename T>
class CNode
{
private:
    T m_Data;
    CNode* m_Next;
public:
    //constructor
    CNode (const T & Data = T(), CNode* Next = nullptr) : m_Data (Data), m_Next (Next) {}
    //destructor
    ~CNode ()
    {
        cout << m_Next << endl;
        delete m_Next;
    }

    //getter / setter
    T getData(){return m_Data;}
    void setData(const T & Data){m_Data = Data;}
    CNode* getNext(){return m_Next;}
    void setNext( CNode* & Next){m_Next = Next;}
};

void ListeSimple (void)
{
    std::cout << "ListeSimple : \n\n";

    CNode<int>* Tete = nullptr;

    // Le dernier element cree est toujours le premier de la liste


    for (unsigned i (0); i < 5; ) {
        Tete = new CNode<int> (i++, Tete);
        std::cout << Tete << endl;
    }

    for (CNode<int>* Ptr (Tete); Ptr; Ptr = Ptr->getNext())
        std::cout << Ptr->getData() << "; ";

    std::cout << '\n';

    // Dans cette version, le destructeur de C1Link detruit son
    //   suivant donc la destruction de la liste est recursive

    delete Tete;

}// ListeSimple ()

//Exo2

template <typename T>
class CList
{
private:
    CNode<T>* m_fictionalHead;
    CNode<T>* m_Queue;
public:
    CList () { m_fictionalHead = new CNode<int> (999, nullptr); }
    ~CList () {delete m_fictionalHead;}
   //ajout en tête de liste
    void push_front (const T & val) {
            CNode<int>* ptrTmp = new CNode<int> (val, m_fictionalHead->getNext());
            m_fictionalHead->setNext(ptrTmp);
            if (ptrTmp->getNext() == nullptr) m_Queue = ptrTmp;
        }
   //affichage
    void Show () const
    {
        for (CNode<T>* ptr (m_fictionalHead); ptr != nullptr; ptr = ptr->getNext ())
            cout << ptr->getData () << "; ";
    }
    //recherche d'un élément dans la liste, renvoie le pointeur du maillon si l'élément est présent, nullptr sinon
    CNode<T>* Find (const T & val) const
    {
        CNode<T>* ptr (m_fictionalHead);
        for ( ; ptr != nullptr && ptr->getData () != val
             ; ptr = ptr->getNext ());

        return ptr;
    }
    //ajout d'une valeur après un maillon de la liste
    void Add (const T & val, CNode<T>* ptr)
    {
        if (nullptr == ptr) return;
        CNode<T>* ptrTmp = new CNode<T> (val, ptr->getNext ());
        ptr->getNext ();
        if (ptr->getNext() == nullptr) m_Queue = ptr;


    }
    //détache un maillon de la liste et le supprime
    void Delete (CNode<T>* pDelete)
    {
        CNode<T>* pFind (m_fictionalHead);
        for ( ; pFind->getNext () != pDelete ;
               pFind = pFind->getNext ())
            if (pFind->getNext () == nullptr) return;

        pFind->setNext (pDelete->getNext ());
        pDelete->setNext (nullptr);

        delete pDelete;
    }
    void push_back (const T & val){
        CNode<T>* pTmp = new CNode<T> (val, nullptr);
            m_Queue->setNext(pTmp);
            m_Queue = pTmp;
    };

};

void ListeSimpleV2 ()
{
    cout << "ListeSimpleV2 : \n\n";

    CList<int> AList;

    // Le dernier element cree est toujours le premier de la liste

    for (unsigned i (0); i < 5; )
    {
        AList.push_back(i++);
    }

    AList.Show ();

    int i;
    cin >>i;
    CNode<int>* ptr = AList.Find (i);
    AList.Add (3*i, ptr);
    AList.Show ();

    cout << ((ptr != NULL)?  " " : "non ") << "trouve" << endl;

}

int main()
{
    ListeSimple();
    ListeSimpleV2();

    return 0;
}


