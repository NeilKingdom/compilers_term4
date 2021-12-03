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
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
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

BufferPointer create(sofia_int size, sofia_int increment, sofia_int mode) {
	BufferPointer b;
	/* TO_DO: Defensive programming */
	if (size<0 || size>SOFIA_MAX_SIZE)
		return NULL;
	if (!size) {
		size = BUFFER_DEFAULT_SIZE;
		increment = BUFFER_DEFAULT_INCREMENT;
	}
	if (!increment)
		mode = MODE_FIXED;
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	/* TO_DO: Defensive programming */
	if (b == NULL)
		return NULL;
	b->content = (sofia_chr*)malloc(size);
	/* TO_DO: Defensive programming */
	if (!b->content) {
		free(b);
		return NULL;
	}
	b->mode = mode;
	b->size = size;
	b->increment = increment;
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
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

BufferPointer addChar(BufferPointer const pBuffer, sofia_chr ch) {
	sofia_chr* tempbuf;
	sofia_int newSize;
	/* TO_DO: Defensive programming */
	/* TO_DO: Reset Realocation */
    /* TO_DO: Check FUL */
	if (pBuffer->size == pBuffer->position.writePos * (sofia_int)sizeof(sofia_chr)) {
		switch (pBuffer->mode) {
		case MODE_FIXED:
			/* TO_DO: Set FUL */
			return NULL;
		case MODE_ADDIT:
			newSize = pBuffer->size + pBuffer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < 0 || newSize <= pBuffer->size) {
				return NULL;
			}
			break;
		case MODE_MULTI:
			newSize = pBuffer->size * pBuffer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < 0 || newSize <= pBuffer->size) {
				return NULL;
			}
			break;
		default:
			return NULL;
		}
		tempbuf = (sofia_chr*)realloc(pBuffer->content, newSize);
		/* TO_DO: Defensive programming */
		if (tempbuf && tempbuf != pBuffer->content) {
			/* TO_DO: Set Relocation */
			pBuffer->content = tempbuf;
		}
		pBuffer->size = newSize;
	}
	/* TO_DO: Adjust flags: Reset EMP */
	/* TO_DO: Adjust flags: Set FUL if necessary */
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
sofia_bol clear(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.writePos = pBuffer->position.markPos = pBuffer->position.readPos = 0;
	/* TO_DO: Adjust flags original */
	return SOFIA_TRUE;
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
sofia_bol destroy(BufferPointer const pBuffer) {
	free(pBuffer->content);
	free(pBuffer);
	return SOFIA_TRUE;
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
sofia_bol isFull(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Use bitwise check to test if buffer is FUL */
	if (pBuffer->size == pBuffer->position.writePos * (sofia_int)sizeof(sofia_chr))
		return SOFIA_TRUE;
	return SOFIA_FALSE;
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
sofia_int getWritePos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
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
sofia_int getSize(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
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
sofia_int getMode(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
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
sofia_int getMarkPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
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
sofia_bol setMark(BufferPointer const pBuffer, sofia_int mark) {
	/* TO_DO: Defensive programming */
	pBuffer->position.markPos = mark;
	return SOFIA_TRUE;
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
sofia_int print(BufferPointer const pBuffer) {
	sofia_int cont = 0;
	sofia_chr c;
	/* TO_DO: Defensive programming */
	c = getChar(pBuffer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (!(pBuffer->position.readPos == pBuffer->position.writePos)) {
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
sofia_int load(BufferPointer const pBuffer, FILE* const fi) {
	sofia_int size = 0;
	sofia_chr c;
	/* TO_DO: Defensive programming */
	c = (sofia_chr)fgetc(fi);
	while (!feof(fi)) {
		if (!addChar(pBuffer, c)) {
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
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
sofia_bol isEmpty(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Use bitwise operation to test if buffer is EMP */
	if (pBuffer->position.writePos==0)
		return SOFIA_TRUE;
	return SOFIA_FALSE;
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
sofia_chr getChar(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	if (pBuffer->position.readPos == pBuffer->position.writePos) {
		/* TO_DO: Set EOB flag */
		return BUFFER_EOF;
	}
	/* TO_DO: Reset EOB flag */
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
sofia_bol recover(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos = 0;
	pBuffer->position.markPos = 0;
	return SOFIA_TRUE;
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
sofia_bol retract(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos--;
	return SOFIA_TRUE;
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
sofia_bol restore(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	pBuffer->position.readPos = pBuffer->position.markPos;
	return SOFIA_TRUE;
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
sofia_int getReadPos(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
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
sofia_int getIncrement(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
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
sofia_chr* getContent(BufferPointer const pBuffer, sofia_int pos) {
	/* TO_DO: Defensive programming */
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
sofia_flg getFlags(BufferPointer const pBuffer) {
	/* TO_DO: Defensive programming */
	return pBuffer->flags;
}
