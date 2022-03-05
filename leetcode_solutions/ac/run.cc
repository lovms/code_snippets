#include <string>
#include <iostream>
#include <locale>
#include <set>
#include <vector>
#include <algorithm>
#include <cwchar>
#include <codecvt>
#include <fstream>

const int use_prefix_suffix_dedup = 0;
void lcs(const std::wstring& str1, const std::wstring& str2, int& lcs_seq, int& lcs_str) {
    lcs_seq = 0;
    lcs_str = 0;
    int size1 = str1.length();
    int size2 = str2.length();
    std::vector<int> comm_seq_vec, comm_str_vec;
    comm_seq_vec.resize((size1 + 1) * (size2 + 1));
    comm_str_vec.resize((size1 + 1) * (size2 + 1));

    for (int i = 0; i < size1; ++i) {
      comm_seq_vec[i * (size2 + 1) + 0] = 0;
      comm_str_vec[i * (size2 + 1) + 0] = 0;
    }
    for (int i = 0; i < size2; ++i) {
      comm_seq_vec[0 * (size2 + 1) + i] = 0;
      comm_str_vec[0 * (size2 + 1) + i] = 0;
    }

    for (int i = 1; i <= size1; ++i) {
      for (int j = 1; j <= size2; ++j) {
        if (str1[i - 1] == str2[j - 1]) {
          comm_seq_vec[i * (size2 + 1) + j] = comm_seq_vec[(i - 1) * (size2 + 1) + (j - 1)] + 1;
          comm_str_vec[i * (size2 + 1) + j] = comm_str_vec[(i - 1) * (size2 + 1) + (j - 1)] + 1;
          lcs_str = std::max(lcs_str, comm_str_vec[i * (size2 + 1) + j]);
        } else {
          comm_seq_vec[i * (size2 + 1) + j] =
              std::max(comm_seq_vec[(i - 1) * (size2 + 1) + j], comm_seq_vec[i * (size2 + 1) + j - 1]);
          comm_str_vec[i * (size2 + 1) + j] = 0;
        }
      }
    }

    lcs_seq = comm_seq_vec[size1 * (size2 + 1) + size2];
}

bool is_text_dedup(const std::string& str1, const std::string& str2) {

//std::cout << "compare words: " << str1 << " vs. " << str2 << std::endl;
std::wstring_convert<std::codecvt_utf8<wchar_t> > wcv;
std::wstring wstr1 = wcv.from_bytes(str1);
std::wstring wstr2 = wcv.from_bytes(str2);

/*
if (use_prefix_suffix_dedup == 1) {
	// judge replication by common prefix or suffix
	int common_prefix_len = 0;
	int common_suffix_len = 0;

	int sz1 = wstr1.size();
	int sz2 = wstr2.size();
	int sz = sz1 > sz2 ? sz2 : sz1;
	for (int i = 0; i < sz; ++i) {
		if (wstr1[i] == wstr2[i]) {
			common_prefix_len++;
		} else {
			break;
		}
	}

	for (int i = 0; i < sz; ++i) {
		if (wstr1[sz1-i-1] == wstr2[sz2-i-1]) {
			common_suffix_len++;
		}
	}

	if (common_prefix_len > 1 || common_suffix_len > 1) {
		return true;
	}
	return false;
}*/

int lcs_seq = 0;
int lcs_str = 0;
lcs(wstr1, wstr2, lcs_seq, lcs_str);

int max_lcsseq = 5;
int max_lcsstr = 4;
/*
if (lcs_seq >= get_conf_value(dedup_conf_dict, "max_lcsseq", 5)
    || lcs_str >= get_conf_value(dedup_conf_dict, "max_lcsstr", 4)) {
  return true;
}
*/

int min_length = std::min(wstr1.size(), wstr2.size());
int max_length = std::max(wstr1.size(), wstr2.size());
int contains_remove = 1;
if (lcs_seq >= min_length && contains_remove == 1) {
  std::cout << "contained query" << std::endl;
  return true;
}

std::set<wchar_t> wchars1(std::begin(wstr1), std::end(wstr1));
std::set<wchar_t> wchars2(std::begin(wstr2), std::end(wstr2));
std::set<wchar_t> wchar_insert, wchar_union;
std::set_intersection(wchars1.begin(), wchars1.end(), wchars2.begin(), wchars2.end(),
                      std::inserter(wchar_insert, wchar_insert.begin()));
//std::set_union(wchars1.begin(), wchars1.end(), wchars2.begin(), wchars2.end(),
//               std::inserter(wchar_union, wchar_union.begin()));

float overlap_ratio = 100 * wchar_insert.size() / (wstr1.size() + wstr2.size());
//float overlap_thresh = 28;
float overlap_thresh = 20;

/*
std::cout << "overlap_ratio: " << overlap_ratio << std::endl
          << "min_len: " << min_length << std::endl
          << "max_len: " << max_length << std::endl
          << "lcs_seq: " << lcs_seq << std::endl
          << "lcs_str: " << lcs_str << std::endl
          << "overlap_size: " << wchar_insert.size() << std::endl;
		  */
std::cout << "compare words: " << str1 << " vs. " << str2 << " :" << overlap_ratio << std::endl;
//if (100 * wchar_insert.size() / (wstr1.size() + wstr2.size()) >= overlap_thresh
if (overlap_ratio >= overlap_thresh
    && min_length >= 2) {
  return true;
}

return false;
}

int main() {
	std::ifstream inf;
	inf.open("./input");
	std::string str1 = "";
	std::string str2 = "";
	while (inf >> str1 >> str2) {

		if (is_text_dedup(str1, str2)) {
			//std::cout << "Hit on Strategy!" << std::endl;
		}
		std::cout << "===================================" << std::endl;
	}
    return 0;
}
