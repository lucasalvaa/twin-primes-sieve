# Twin Primes Sieve

Coding project for the Analysis I exam.

**[Twin primes](https://en.wikipedia.org/wiki/Twin_prime)** are pairs of primes that differ by 2, such as (5, 7), (11, 13), and (17, 19).  
This program efficiently identifies such pairs in a given range using number theory and parallel computation.

---

🧠 How It Works

- This program is based on the [number theory fact](https://www.sciencedirect.com/science/article/abs/pii/S0960077907009812) that primes >3 are of the form 6k ± 1.
- A set of four modular selection rules eliminates k-values that cannot generate twin primes.
- The remaining values of k are transformed into candidate twin pairs (6k+5, 6k+7).
- The statistics of each program run (range, pairs found and time elapsed) are saved in a text file called "resumes.txt".
- The pairs of twin primes found are saved in a text file called "output.txt". This file is overwritten on every run.
   
---

## 📦 Build Instructions

Requires a C compiler (e.g., `gcc`) and `make`.

```bash
git clone https://github.com/your-username/twin-primes-sieve.git
cd twin-primes-sieve
make
```

## 🚀 Usage

```bash
./sieve <lower_bound> <upper_bound>
```

Example:
```bash
./sieve 1 100000000
```

## 👤 Author

Developed by Salvatore Luca [@lucasalvaa](https://github.com/lucasalvaa) and Squitieri Andrea [@Andeser-rgb](https://github.com/Andeser-rgb)
