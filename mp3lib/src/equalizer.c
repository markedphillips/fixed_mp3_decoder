//.. (c) 1998-2018 Mark Phillips Copyright

#include "mp3.h"
#include "real.h"

//#define REAL_FLOAT(x) ((Real)((x) * 32768.0))

void init_spline(float *x, float *y, int n, float *y2)
{
	int i, k;
	float p, qn, sig, un, u[20];

	if (n > 20)
		return;

	y2[0] = u[0] = 0.0;

	for (i = 1; i < n - 1; i++)
	{
		sig = ((float) x[i] - x[i - 1]) / ((float) x[i + 1] - x[i - 1]);
		p = sig * y2[i - 1] + 2.0;
		y2[i] = (sig - 1.0) / p;
		u[i] = (((float) y[i + 1] - y[i]) / (x[i + 1] - x[i])) -
			(((float) y[i] - y[i - 1]) / (x[i] - x[i - 1]));
		u[i] = (6.0 * u[i] / (x[i + 1] - x[i - 1]) - sig * u[i - 1]) / p;
	}
	qn = un = 0.0;

	y2[n - 1] = (un - qn * u[n - 2]) / (qn * y2[n - 2] + 1.0);
	for (k = n - 2; k >= 0; k--)
		y2[k] = y2[k] * y2[k + 1] + u[k];

}

float eval_spline(float xa[], float ya[], float y2a[], int n, float x)
{
	int klo, khi, k;
	float h, b, a;

	klo = 0;
	khi = n - 1;
	while (khi - klo > 1)
	{
		k = (khi + klo) >> 1;
		if (xa[k] > x)
			khi = k;
		else
			klo = k;
	}
	h = xa[khi] - xa[klo];
	a = (xa[khi] - x) / h;
	b = (x - xa[klo]) / h;
	return (a * ya[klo] + b * ya[khi] + ((a * a * a - a) * y2a[klo] + (b * b * b - b) * y2a[khi])
		* (h * h) / 6.0);
}

void calculate_eq_presets(float preamp, float *b, Real *out)
{
	float x[] =
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, yf[10], val, band[10];
	int bands[] =
	{0, 4, 8, 16, 26, 78, 157, 313, 366, 418};
	int i, j;

	for (i = 0; i < 10; i++)
	{
		band[i] = b[i] + preamp;
	}

	init_spline(x, band, 10, yf);
	for (i = 0; i < 9; i++)
	{
		for (j = bands[i]; j < bands[i + 1]; j++)
		{
			val = eval_spline(x, band, yf, 10, i + ((float) (j - bands[i]) * (1.0 / (bands[i + 1] - bands[i]))));
			out[j] = REAL_FLOAT(pow(2, val / 10.0));
		}
	}
	for (i = bands[9]; i < 576; i++)
		out[i] = out[bands[9] - 1];
}

void calculate_sonique_eq_presets(float preamp, float *b, Real *out)
{
	float x[] =
	{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, yf[20], val, band[20];
	int bands[] =
	{0, 2, 4, 6, 8, 12, 16, 21, 26, 52, 78, 117, 157, 235, 313, 339, 366, 392, 418, 497};
	int i, j;

	for (i = 0; i < 20; i++)
	{
		band[i] = b[i] + preamp;
	}

	init_spline(x, band, 20, yf);
	for (i = 0; i < 19; i++)
	{
		for (j = bands[i]; j < bands[i + 1]; j++)
		{
			val = eval_spline(x, band, yf, 20, i + ((float) (j - bands[i]) * (1.0 / (bands[i + 1] - bands[i]))));
			out[j] = REAL_FLOAT(pow(2, val / 20.0));
		}
	}
	for (i = bands[19]; i < 576; i++)
		out[i] = out[bands[19] - 1];
}
