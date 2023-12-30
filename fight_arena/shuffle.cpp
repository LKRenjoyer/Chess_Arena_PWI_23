#include<bits/stdc++.h>

#define st first
#define nd second
#define pb(x) push_back(x)
#define pp(x) pop_back(x)
#define mp(a, b) make_pair(a, b)
#define all(x) (x).begin(), (x).end()
#define rev(x) reverse(all(x))
#define sor(x) sort(all(x))
#define sz(x) (int)(x).size()
#define rsz(x) resize(x)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii > vii;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef string str;
#define BOOST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); 

#include <unistd.h> 

mt19937 gen(getpid()); 

int main(){ 
	vector<string> V; 
	string s; 
	int n = 200; 
	for(int i = 0; i < n; i++){ 
		getline(cin, s); 
		if(sz(s) < 6){ 
			assert(1 == 0); 
			exit(0);  
		} 
		s = s.substr(5); 
		V.pb(s); 
		getline(cin,s); 
		getline(cin,s); 
	} 
	vi per; per.resize(n); 
	for(int i = 0; i < n;i++) 
		per[i] = i; 
	shuffle(per.begin(), per.end(), gen); 
	for(int i = 0; i < n; i++) 
		cout << V[per[i]] << "\n"; 
}
