package tree.trie;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

/**
 * 字典树
 * 数组实现
 * 
 * 字符集是 26个小写字母，
 * 
 * 如果需要字符集多，可以修改成 map 存储
 */
public class Trie {

    /**
     * ArrayList 默认为空
     */
    private ArrayList<Trie> children = new ArrayList<>(Collections.nCopies(26, null));
    private boolean isEnd;

    public void insert(String word) {
        int n = word.length();
        Trie p = this;
        for (int i = 0; i < n; i++) {
            char c = word.charAt(i);
            int index = c - 'a';
            if (p.children.get(index) == null) {
                p.children.set(index, new Trie());
            }
            p = p.children.get(index);
        }
        p.isEnd = true;
    }

    public boolean search(String word) {
        Trie trie = searchPrefix(word);
        return trie != null && trie.isEnd;
    }

    public boolean startsWith(String prefix) {
        return searchPrefix(prefix) != null;
    }

    private Trie searchPrefix(String prefix) {
        int n = prefix.length();
        Trie p = this;
        for (int i = 0; i < n; i++) {
            char c = prefix.charAt(i);
            int index = c - 'a';
            if (p.children.get(index) == null) {
                return null;
            }
            p = p.children.get(index);
        }
        return p;
    }
}
