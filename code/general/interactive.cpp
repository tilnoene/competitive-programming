// you should use cout.flush() every cout
int query(int a) {
    cout << "? " << a << '\n';
    cout.flush();
    char res; cin >> res;
    return res;
}

// using endl you don't need
int query(int a) {
    cout << "? " << a << endl;
    char res; cin >> res;
    return res;
}