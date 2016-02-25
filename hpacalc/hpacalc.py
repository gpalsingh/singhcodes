class Fraction(object):
    def __init__(self, nume=0, denom=0):
        #do cleaning
        self.num = num
        self.den = denom

    def __getAttrs(self):
        return (self.num, self.den)

    def reciprocal(self, other):
        n, d = self.__getAttrs()
        return Fraction(d, n)

    def __add__(self, other):
        sn, sd = self.__getAttrs()
        on, od = other.__getAttrs()
        newn = sn * od + sd * on
        newd = sd * od
        return Fraction(newn, newd)
        
    def __div__(self, other):
        return self * other.reciprocal()
        
    __truediv__ = __div__
    
    def __mul__(self, other):
        sn, sd = self.__getAttrs()
        on, od = other.__getAttrs()
        newn = sn * on
        newd = sd * od
        return Fraction(newn, newd)
        
    #check this
    def __sub__(self, other):