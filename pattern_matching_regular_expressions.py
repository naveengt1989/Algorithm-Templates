
# coding: utf-8

# In[28]:

'''
Created on May 23, 2016

@author: naveengt1989
'''
# Reference: https://regex101.com/
# http://docs.python.org/2/howto/regex.html
# https://developers.google.com/edu/python/regular-expressions?csw=1
import re

parts = [
    r'(?P<host>\S+)',                   # host %h
    r'\S+',                             # indent %l (unused)
    r'(?P<user>\S+)',                   # user %u
    r'\[(?P<time>.+)\]',                # time %t
    r'"(?P<request>.+)"',               # request "%r"
    r'(?P<status>[0-9]+)',              # status %>s
    r'(?P<size>\S+)',                   # size %b (careful, can be '-')
]

pattern = '(?P<first>\S+)(\s+)(?P<second>[0-9a-zA-Z]+)'
data = 'naveen stupid 1243'
res = re.match(pattern,data)
print res.group('first')
print res.group('second')



# In[111]:

import re
#########################################################
# []+?, []*?      => match only sufficient elements so as to get a match.
pattern_greedy = '35[\w]+35'
pattern_nongreedy = '35[\w]+?35'
pattern_greedy_overlap = '(?=(35[\w]+35))'
pattern_nongreedy_overlap = '(?=(35[\w]+?35))'
data = "wdwdw35rrrgrdv35dededede35dcdcd35"
res_greedy = re.findall(pattern_greedy,data)
res_nongreedy = re.findall(pattern_nongreedy,data)
res_greedy_overlap = re.findall(pattern_greedy_overlap,data)
res_nongreedy_overlap = re.findall(pattern_nongreedy_overlap,data)
print res_greedy, res_nongreedy, res_greedy_overlap, res_nongreedy_overlap


# In[98]:

import re
#########################################################
pattern_greedy = '([^,\s]+)'

data = "naveen,    jinde, arjun,deepak"
res_greedy = re.findall(pattern_greedy,data)

print res_greedy


# In[36]:

import re
#########################################################
pattern_greedy = 'r(\S+)r'

data = "aaaaardfgraaaaa"
res_greedy = re.findall(pattern_greedy,data)

print res_greedy


# In[47]:

import re
#########################################################
pattern_greedy = '(\S+)(?:$|\s|,)'
pattern_lazy = '(\S+?)(?:$|,|\s)'
data = "aaaaardf   graaaaa,naveen"
res_greedy = re.findall(pattern_greedy,data)
res_lazy = re.findall(pattern_lazy,data)
print res_greedy
print res_lazy


# In[4]:

import re
pattern = '\S+\.?$'
data = '401 Southwest Parkway.'
res = re.findall(pattern,data)
print res


# In[8]:

import re
pattern = '[^\{\}\|]+'
data = '{1.01787e+08|1.019e+08}'
res = re.findall(pattern,data)
print res
print float(res[0]), float(res[1])


# In[2]:

import re
pattern = "(.*)friend(.*)"
data = "naveen is a good friend to have"
res = re.findall(pattern,data)
print res


# In[53]:

# search for non alphanumeric characters
import re
pattern = "[^\w]"  # detect individually
#pattern = "[^\w]+"
data= "naveen$#"
res = re.findall(pattern, data)
print res


# In[50]:

import re
#########################################################
pattern_nonoverlap = '([\d]{4,4})'
pattern_overlap = '(?=([\d]{4,4}))'
# ?=   => to make RE copture overlapping patterns
data = "1234567"
res_nonoverlap = re.findall(pattern_nonoverlap,data)
res_overlap = re.findall(pattern_overlap,data)
print res_nonoverlap
print res_overlap


# In[47]:

import re
#########################################################
# validate IP address
# ?:   => to make brackets non-capturing
pattern_ip = '((?:(?:[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}(?:[0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))'

data = "192.168.1.2, 192.168.255.255,1.2.3.4,1.2.3,1.2.0.0,10.0.0.0"
res = re.findall(pattern_ip,data)

print res


# In[109]:

import re
#########################################################
greedypattern = '[\d]+\d'
lazypattern = '[\d]+?\d'
# ?=   => to make RE copture overlapping patterns
data = "1234"
res_greedy = re.findall(greedypattern,data)
res_lazy = re.findall(lazypattern,data)
print res_greedy, res_lazy


# In[ ]:




# In[ ]:



