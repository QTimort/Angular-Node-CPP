function main() {
	var low, high, temp, i;
	var isPrime;

	low = 0;
	high = 600000;
	//cout << "Enter two numbers (intevals): ";
	//cin >> low >> high;

	//swapping numbers if low is greater than high
	if (low > high) {
		temp = low;
		low = high;
		high = temp;
	}
	//cout << "\nPrime numbers between " << low << " and " << high << " are:" << endl;

	while (low < high) {
		isPrime = true;
		if (low == 0 || low == 1) {
			isPrime = false;
		}
		else {
			for (i = 2; i <= low / 2; ++i) {
				if (low % i == 0) {
					isPrime = false;
					break;
				}
			}
		}

		if (isPrime)
			process.stdout.write(low + " ");
		++low;
	}
}

main();