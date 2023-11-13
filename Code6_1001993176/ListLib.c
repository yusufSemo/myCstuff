/*yusuf semo 1001993176 ListLib */

#include "ListLib.h"
void AddDrawCommandToList(char Letter, char DrawCommand[], NODE **LinkedListHead)
{
	/* declare pointers of type NODE named TempPtr and NewNode */
	NODE *TempPtr = malloc(sizeof(NODE)*sizeof(char)+1);;
	NODE *NewNode;
    
	/* malloc a new node and assign the Letter and the DrawCommand (after mallocing memory for it) */
	NewNode = malloc(sizeof(NODE)*sizeof(char)+1);
	NewNode->Letter = Letter;
	NewNode->DrawCommand = DrawCommand;
	NewNode->next_ptr = NULL;

	/* If the LinkedListHead is NULL, then give it the address of the new node */
	if(LinkedListHead == NULL)
	{
		*LinkedListHead = NewNode;
	}
	/* Else traverse to the end of the linked list and add the new node */
	else
	{
		while(TempPtr != NULL)
		{
			TempPtr = TempPtr->next_ptr;
		}
		//TempPtr->next_ptr = NewNode;
	}
}

NODE* FindLetter(NODE *LinkedListHead, char Letter, char DC[])
{
	/* while traversing the linked list AND the Letter in the node is not the
	Letter passed in */
	NODE* tempPtr = LinkedListHead;
	while(tempPtr != NULL && tempPtr->Letter != Letter)
	{
		/* move TempPtr */
		tempPtr = tempPtr->next_ptr;
	}
	if (tempPtr != NULL)
	{
		strcpy(DC, tempPtr->DrawCommand);
        return tempPtr->next_ptr;
		/* copy the DrawCommand from the node into the passed in parameter */
		/* return the next pointer stored in TempPtr */
	}
	else
	{
		memset(DC, '\0', sizeof(*DC)); //Set DC to NULLs to signal that we
		//found all of the nodes for this letter
		/* return TempPtr */
		return tempPtr;
		
	}
}



