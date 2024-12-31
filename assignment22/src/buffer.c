/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / Daniel Cormier
*************************************************************/

/************************************************************
* File name: buffer.c
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: Sep 01 2021
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer (A12)
*************************************************************/

#ifndef COMPILERS_H_
#include "../deps/compilers.h"
#endif

#ifndef BUFFER_H_
#include "../deps/buffer.h"
#endif

/************************************************************
* Function name: create
* Purpose: Creates the buffer according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: Ver 2.1
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to Buffer)
* Algorithm: Allocation of memory according to inicial (default) values.
* TO_DO:
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
**************************************************************/

BufferPointer create(pheonix_int size, pheonix_int increment, pheonix_int mode) {
	BufferPointer b;
	/* TO_DO: Defensive programming */
	/* Do not use getSize() since pBuffer->size has not been initialized yet */
	if (size < 0 || size > PHEONIX_MAX)
		return NULL;

	if(increment < 0)
		return NULL;

	if(mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI)
		return NULL;

	if (!size) {
		size = BUFFER_DEFAULT_SIZE;
		increment = BUFFER_DEFAULT_INCREMENT;
	}
	if (!increment)
		mode = MODE_FIXED;
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	/* TO_DO: Defensive programming */
	if (b == NULL) {
		free(b);
		return NULL;
	}
	b->content = (pheonix_char*)malloc(size);
	/* TO_DO: Defensive programming */
	if ((b->content) == NULL) {
		free(b->content);
		free(b);
		return NULL;
	}
	b->mode = mode;
	b->size = size;
	b->increment = increment;
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
	b->flags = PHEONIX_DEF;
	b->flags |= PHEONIX_EMP;
	return b;
}


/************************************************************
* Function name: addChar
* Purpose: Adds a char to buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   ch = char to be added
* Return value:
*	bPointer (pointer to Buffer)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/

BufferPointer addChar(BufferPointer pBuffer, pheonix_char ch) {
	pheonix_char* tempbuf;
	pheonix_int newSize;
	/* TO_DO: Defensive programming */
	/* TO_DO: Reset Realocation */
    /* TO_DO: Check FUL */
	if (isFull(pBuffer)) {
		pBuffer->flags |= PHEONIX_FUL;
		switch (pBuffer->mode) {
		case MODE_FIXED:
			/* TO_DO: Set FUL */
			pBuffer->flags |= PHEONIX_FUL;
			/* Cannot allocate more memory in fixed mode so end function */
			return NULL;
		case MODE_ADDIT:
			if(getSize(pBuffer) == BUFFER_ERROR)
				return NULL;

			newSize = pBuffer->size + pBuffer->increment;
			/* TO_DO: Defensive programming */
			if(newSize < 0 || newSize <= pBuffer->size)
				return NULL;
			break;
		case MODE_MULTI:
			if(getSize(pBuffer) == BUFFER_ERROR)
				return NULL;

			newSize = pBuffer->size * pBuffer->increment;
			/* TO_DO: Defensive programming */
			if(newSize < 0 || newSize <= pBuffer->size)
				return NULL;
			break;
		default:
			return NULL;
		}
		tempbuf = (pheonix_char*)realloc(pBuffer->content, newSize);
		/* TO_DO: Defensive programming */
		if(tempbuf == NULL) {
			free(tempbuf);
			return NULL;
		}
		if (tempbuf && tempbuf != pBuffer->content) {
			/* TO_DO: Set Relocation */
			pBuffer->flags |= PHEONIX_REL;
			pBuffer->content = tempbuf;
		}
		pBuffer->size = newSize;
	}
	/* TO_DO: Adjust flags: Reset EMP */
	/* TO_DO: Adjust flags: Set FUL if necessary */
	pBuffer->flags &= PHEONIX_RESET_EMP;

	pBuffer->content[pBuffer->position.writePos++] = ch;
	return pBuffer;
}

/************************************************************
* Function name: clear
* Purpose: Clears the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool clear(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;

	if(pBuffer == NULL)
		return PHEONIX_FALSE;

	if(pBuffer->position.writePos || pBuffer->position.markPos || pBuffer->position.readPos) {
		return PHEONIX_FALSE;
	}

	/* TO_DO: Adjust flags original */
	pBuffer->flags &= PHEONIX_DEF;
	return PHEONIX_TRUE;
}

/************************************************************
* Function name: destroy
* Purpose: Releases the buffer address
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool destroy(BufferPointer pBuffer) {

	/* If content isn't empty free it */
	if(pBuffer->content)
		free(pBuffer->content);

	free(pBuffer);
	return PHEONIX_TRUE;
}

/************************************************************
* Function name: isFull
* Purpose: Checks if buffer is full
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool isFull(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Use bitwise check to test if buffer is FUL */
	if(pBuffer == NULL)
		return PHEONIX_TRUE;

	if((pBuffer->flags & PHEONIX_FUL) == PHEONIX_FUL)
		return PHEONIX_TRUE;

	if (pBuffer->position.writePos * (pheonix_int)sizeof(pheonix_char) >= pBuffer->size)
		return PHEONIX_TRUE;

	return PHEONIX_FALSE;
}

/************************************************************
* Function name: getWritePos
* Purpose: Returns the position of char to be added
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	addcPosition value
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int getWritePos(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	if(pBuffer->position.writePos < 0 || pBuffer->position.writePos > pBuffer->size)
		return BUFFER_ERROR;

	if(pBuffer->position.writePos > PHEONIX_MAX)
		return BUFFER_ERROR;

	return pBuffer->position.writePos;
}

/************************************************************
* Function name: getSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int getSize(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	if(!pBuffer->size)
		return BUFFER_ERROR;

	if(pBuffer->size < 0 || pBuffer->size > PHEONIX_MAX)
		return BUFFER_ERROR;

	return pBuffer->size;
}

/************************************************************
* Function name: getMode
* Purpose: Returns the operational mode
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int getMode(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	if(!pBuffer->mode)
		return BUFFER_ERROR;

	if(pBuffer->mode != MODE_FIXED && pBuffer->mode != MODE_ADDIT && pBuffer->mode != MODE_MULTI)
		return BUFFER_ERROR;

	return pBuffer->mode;
}


/************************************************************
* Function name: getMarkPos
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	mark offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int getMarkPos(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	if(pBuffer->position.markPos < 0 || pBuffer->position.markPos > pBuffer->size)
		return BUFFER_ERROR;

	return pBuffer->position.markPos;
}


/************************************************************
* Function name: setMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool setMark(BufferPointer pBuffer, pheonix_int mark) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return PHEONIX_FALSE;

	if(mark < 0 || mark > pBuffer->size)
		return PHEONIX_FALSE;

	pBuffer->position.markPos = mark;
	return PHEONIX_TRUE;
}

/************************************************************
* Function name: print
* Purpose: Prints the string in the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int print(BufferPointer pBuffer) {
	pheonix_int cont = 0;
	pheonix_char c;
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	c = getChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (!(pBuffer->position.readPos == pBuffer->position.writePos)) {
		/* getChar checks for EOB and sets flag if reached */
		if((pBuffer->flags & PHEONIX_EOB) == PHEONIX_EOB)
			return cont;
		cont++;
		printf("%c", c);
		c = getChar(pBuffer);
	}
	return cont;
}

/************************************************************
* Function name: load
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   fi = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int load(BufferPointer pBuffer, FILE* fi) {
	pheonix_int size = 0;
	pheonix_char c;
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	c = (pheonix_char)fgetc(fi);
	while (!feof(fi)) {
		if (!addChar(pBuffer, c)) {
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (pheonix_char)fgetc(fi);
		size++;
	}
	if (ferror(fi))
		return BUFFER_ERROR;
	return size;
}

/************************************************************
* Function name: isEmpty
* Purpose: Checks if buffer is empty.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool isEmpty(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Use bitwise operation to test if buffer is EMP */
	if(pBuffer == NULL)
		return PHEONIX_TRUE;

	if((pBuffer->flags & PHEONIX_EMP) == PHEONIX_EMP)
		return PHEONIX_TRUE;

	if (pBuffer->position.writePos==0)
		return PHEONIX_TRUE;

	return PHEONIX_FALSE;
}

/************************************************************
* Function name: getChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_char getChar(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_EOF;

	/* Leaving this here as a reminder of the pain that it caused */
	/*
	if(!pBuffer->position.readPos)
		return BUFFER_EOF;

	if(!pBuffer->position.writePos)
		return BUFFER_EOF;
	*/

	if (pBuffer->size == pBuffer->position.writePos * (pheonix_int)sizeof(pheonix_char)) {
	/*if (pBuffer->position.readPos == pBuffer->position.writePos) {*/
		/* TO_DO: Set EOB flag */
		pBuffer->flags |= PHEONIX_EOB;
		return BUFFER_EOF;
	}
	/* TO_DO: Reset EOB flag */
	pBuffer->flags &= PHEONIX_RESET_EOB;
	return pBuffer->content[pBuffer->position.readPos++];
}


/************************************************************
* Function name: recover
* Purpose: Rewinds the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool recover(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return PHEONIX_FALSE;

	/*if(!pBuffer->position.readPos)
		return PHEONIX_FALSE;

	if(!pBuffer->position.markPos)
		return PHEONIX_FALSE;*/

	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return PHEONIX_TRUE;
}


/************************************************************
* Function name: retract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool retract(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return PHEONIX_FALSE;

	if(!pBuffer->position.readPos)
		return PHEONIX_FALSE;

	if(pBuffer->position.readPos <= 0)
		return PHEONIX_FALSE;

	pBuffer->position.readPos--;
	return PHEONIX_TRUE;
}


/************************************************************
* Function name: restore
* Purpose: Resets the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_bool restore(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return PHEONIX_FALSE;

	pBuffer->position.readPos = pBuffer->position.markPos;
	return PHEONIX_TRUE;
}


/************************************************************
* Function name: getReadPos
* Purpose: Returns the value of getCPosition.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The readPos offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int getReadPos(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	return pBuffer->position.readPos;
}


/************************************************************
* Function name: getIncrement
* Purpose: Returns the buffer increment.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_int getIncrement(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return BUFFER_ERROR;

	if(!pBuffer->increment)
		return BUFFER_ERROR;

	return pBuffer->increment;
}


/************************************************************
* Function name: getContent
* Purpose: Returns the pointer to String.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_char* getContent(BufferPointer pBuffer, pheonix_int pos) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return NULL;

	if(pos < 0 || pos >= pBuffer->size)
		return NULL;

	return pBuffer->content + pos;
}


/************************************************************
* Function name: getFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
**************************************************************/
pheonix_byte getFlags(BufferPointer pBuffer) {
	/* TO_DO: Defensive programming */
	if(pBuffer == NULL)
		return PHEONIX_DEF;

	if(!pBuffer->flags)
		return PHEONIX_DEF;

	return pBuffer->flags;
}
