# given a list of strings, find and remove duplicates
#
# note: the shortcut would be to just do out = set(in), where 'in' is the list :)
#

import unittest

def foo(l):
    if l is []:
        return l

    summary = {}
    for el in l:
        if el in summary:
            summary[el] += 1
        else:
            summary[el] = 1
    return list(summary.keys())

class googleInterview1(unittest.TestCase):
    def test_empty(self):
        l = []
        l = foo(l)
        l.sort()
        self.assertEqual(l, [])

    def test_one(self):
        l = ["one"]
        l = foo(l)
        l.sort()
        self.assertEqual(l, ["one"])

    def test_nochange(self):
        l = ["one", "two"]
        l = foo(l)
        l.sort()
        self.assertEqual(l, ['one', 'two'])

    def test_onerepeated(self):
        l = ['one', 'one']
        l = foo(l)
        l.sort()
        self.assertEqual(l, ['one'])

    def test_many(self):
        l = ['a', 'a', 'b']
        l = foo(l)
        l.sort()
        self.assertEqual(l, ['a', 'b'])

    def test_many2(self):
        l = ['a', 'b', 'b']
        l = foo(l)
        l.sort()
        self.assertEqual(l, ['a', 'b'])

    def test_many3(self):
        l = ['a', 'a', 'b', 'b', 'b', 'c']
        l = foo(l)
        l.sort()
        self.assertEqual(l, ['a', 'b', 'c'])


if __name__ == "__main__":
    unittest.main()
