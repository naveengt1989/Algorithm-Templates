
# coding: utf-8

# In[28]:

'''
Created on May 23, 2016

@author: naveengt1989
'''
# Reference: https://regex101.com/
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



# In[35]:

import re
#########################################################
pattern_greedy = '35[\w]+35'
pattern_nongreedy = '35[\w]+?35'

data = "wdwdw35rrrgrdv35dededede35dcdcd35"
res_greedy = re.findall(pattern_greedy,data)
res_nongreedy = re.findall(pattern_nongreedy,data)

print res_greedy, res_nongreedy


# In[28]:

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


# In[ ]:




# In[ ]:




# In[ ]:



