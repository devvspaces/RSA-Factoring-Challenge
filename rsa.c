#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <sys/types.h>

/**
 * factorize - factorize a string number
 *
 * @cnum: string number
 */
void factorize(char *cnum)
{
	mpz_t num, limit, div, i, i2, inc, inc2, mod, zero, f1;
	mpq_t t1, t2, t3;

	mpz_init(num), mpz_init(limit), mpz_init(i2);
	mpz_init(div), mpz_init(i), mpz_init(mod);
	mpz_init(zero), mpz_init(f1), mpz_init(inc), mpz_init(inc2);
	mpq_init(t1), mpq_init(t2), mpq_init(t3);

	mpz_set_str(num, cnum, 10), mpz_set_str(div, "1", 10);
	mpz_set_str(inc, "6", 10), mpz_set_str(inc2, "2", 10);
	mpz_set_str(zero, "0", 10), mpq_set_ui(t3, 0, 10), mpz_set_str(i, "5", 10);

	mpz_sqrt(limit, num), mpq_set_z(t2, limit);
	if (mpz_mod_ui(f1, num, 2), mpq_set_z(t1, f1), mpq_equal(t1, t3) != 0)
		mpz_set_ui(div, 2);
	else if (mpz_mod_ui(f1, num, 3), mpq_set_z(t1, f1), mpq_equal(t1, t3) != 0)
		mpz_set_ui(div, 3);
	else
		while (mpz_cmp(limit, i) > 0 || mpq_equal(t2, i) != 0)
		{
			if (mpz_mod(mod, num, i), mpq_set_z(t1, mod), mpq_equal(t1, t3) != 0)
			{
				mpz_set(div, i);
				break;
			}
			mpz_add(i2, i, inc2), mpz_mod(mod, num, i2), mpq_set_z(t1, mod);
			if (mpq_equal(t1, t3) != 0)
			{
				mpz_set(div, i2);
				break;
			}
			mpz_add(i, i, inc);
		}
	mpz_divexact(f1, num, div), gmp_printf("%Zd=%Zd*%Zd\n", num, f1, div);
	mpz_clear(num), mpz_clear(limit), mpz_clear(div), mpz_clear(i);
	mpz_clear(mod), mpz_clear(zero), mpz_clear(f1);
	mpq_clear(t1), mpq_clear(t3);
}

/**
 * main - entry point
 *
 * @ac: args count
 * @argv: string args
 *
 * Return: always 0
 */
int main(int ac, char **argv)
{
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if (stream == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	while ((nread = getline(&line, &len, stream)) != -1)
		factorize(line);

	free(line);
	fclose(stream);
	return (0);
}
