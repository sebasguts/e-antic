/*
    Copyright (C) 2016 Vincent Delecroix

    This file is part of e-antic

    e-antic is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "flint.h"
#include "poly_extra.h"
#include "fmpq_vec.h"

int main()
{
    slong iter;

    FLINT_TEST_INIT(state);

    printf("set_rational_roots....");

    for (iter = 0; iter < 100; iter++)
    {
        fmpq * vec;
        fmpz_poly_t p;
        slong n;

        n = n_randint(state, 100);
        vec = _fmpq_vec_init(n);
        _fmpq_vec_randtest(vec, state, n, 100);

        fmpz_poly_init(p);
        fmpz_poly_set_rational_roots(p, vec, n);

        if (fmpz_poly_degree(p) != n)
        {
            printf("ERROR:\n");
            flint_printf("expected degree %wd and got %wd",
                    n, fmpz_poly_degree(p));
            printf("vec = "); _fmpq_vec_print(vec, n); printf("\n");
            printf("p = "); fmpz_poly_print(p); printf("\n");
            abort();
        }

        _fmpq_vec_clear(vec, n);
        fmpz_poly_clear(p);
    }

    FLINT_TEST_CLEANUP(state);

    printf("PASS\n");
    return 0;
}