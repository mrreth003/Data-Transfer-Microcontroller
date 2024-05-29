/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define EI 11  /* typically 10..13 */
#define EJ  4  /* typically 4..5 */
#define P   1  /* If match length <= P then output one character */
#define N (1 << EI)  /* buffer size */
#define F ((1 << EJ) + 1)  /* lookahead buffer size */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
char compressed[110];

int bit_buffer = 0, bit_mask = 128;
unsigned long codecount = 0, textcount = 0;
unsigned char buffer[N * 2];
FILE *infile, *outfile;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void putbit1(void);
void putbit0(void);
void flush_bit_buffer(void);
void output1(int c);
void output2(int x, int y);

void decompression(void);
void decryption(void);
void filter(void);

/* USER CODE END PFP */

int main()
{
    infile = fopen("readSensorData.csv", "rb");
    outfile = fopen("deData.txt", "wb");
    decryption();
    fputs("\n", outfile);
    fclose(infile);
    fclose(outfile);

    infile = fopen("./deData.txt", "rb");
    outfile = fopen("./dedcData.txt", "wb");
    decompression();
    fputs("\n", outfile);
    fclose(infile);
    fclose(outfile);

    infile = fopen("./deData.txt", "rb");
    outfile = fopen("./finalSensorData.txt", "ab");
    filter();
    fputs("\n", outfile);
    fclose(infile);
    fclose(outfile);
}
/* USER CODE BEGIN 4 */

/* DECOMPRESSION */
int getbit(int n) /* get n bits */
{
    int i, x;
    static int buf, mask = 0;
    
    x = 0;
    for (i = 0; i < n; i++) {
        if (mask == 0) {
            if ((buf = fgetc(infile)) == EOF) return EOF;
            mask = 128;
        }
        x <<= 1;
        if (buf & mask) x++;
        mask >>= 1;
    }
    return x;
}

void decompression(void)
{
    int i, j, k, r, c;
    
    for (i = 0; i < N - F; i++) buffer[i] = ' ';
    r = N - F;
    while ((c = getbit(1)) != EOF) {
        if (c) {
            if ((c = getbit(8)) == EOF) break;
            fputc(c-1, outfile);
            buffer[r++] = c;  r &= (N - 1);
        } else {
            if ((i = getbit(EI)) == EOF) break;
            if ((j = getbit(EJ)) == EOF) break;
            for (k = 0; k <= j + 1; k++) {
                c = buffer[(i + k) & (N - 1)];
                fputc(c-1, outfile);
                buffer[r++] = c;  r &= (N - 1);
            }
        }
    }
}


/* DECRYPTION */
void decryption(void)
{
    int c;
	for (int i = 0; i < 110; i++){
        if ((c = fgetc(infile)) == EOF) break;
		fputc(c-57, outfile);
	}
}

/* FILTERING OUTPUT FOR USE IN FILE */
void filter(void) 
{
    int c, cc;
	while ((c = fgetc(infile)) != EOF){
        if (c == 44) cc++;
        if (cc == 7) break;
        fputc(c, outfile);
	}
}
/* USER CODE END 4 */