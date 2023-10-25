/**
 * @file: main.c
 * @brief: String Copy And Capitalize In C To Compare Memory Usage With Assembly Code - Project 1 Module 1
 *
 * @author: Viraj Patel, Kiran jojare
 * @references: 
 *        - Professors Assembly Code in Code1Nucleo.zip 
 *          from Homework2(Practical)
*/

/**
 * @brief: Copy A Null Terminated String From Source Pointer To Destination Pointer
 * @param:
 *     const char *src - Source String Pointer
 *     const char *dst - Destination String Pointer
 * @return: Nothing
 */
 
void my_strcpy(const char *src, char *dst)
{
	// While Source Is Not Null
	while (*src != '\0') {
		// Copy Source To Destination
		*dst = *src;
		// Increment Source And Destination Pointer
		src++;
		dst++;
	}
	// Terminate Destination With Null
	*dst = '\0';
}

/**
 * @brief: Capitalize Every Letter In A Null Terminated String
 * @param:
 *     char *str - Pointer To String To Capitalize
* @return: Nothing
*/

void my_capitalize(char *str)
{
	// While String Is Not Null
	while (*str != '\0') {
		// Check If Character Between a-z
		if ((*str >= 'a') && (*str <= 'z')) {
			// Convert To Uppercase
			*str = *str-32;
		}
		// Increment String Pointer
		str++;
	}
}

int main(void)
{
	const char a[] = "Hello world!";
	char b[20];

	my_strcpy(a, b);
	my_capitalize(b);
	
	while (1);
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************   
