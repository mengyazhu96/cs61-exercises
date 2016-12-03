import urllib2
import time
while True:
	content = urllib2.urlopen('http://cs61.seas.harvard.edu:6164/virginiahall/mission').read().split()
	mission = content[:3]
	x = int(mission[0])
	y = int(mission[1], 16)
	style = mission[2]
	print mission

	for power in xrange(24):
		if pow(2, power) & y != 0:
			url = 'http://cs61.seas.harvard.edu:6164/virginiahall/move?x={0}&y={1}&style={2}'.format(
				x, power, style)
			response = urllib2.urlopen(url)
	time.sleep(0.1)
# print content[1]
# send = 'http://cs61.seas.harvard.edu:6164/virginiahall/move?x={0}&y={1}&style={2}'.format(
# 	int(mission[0]), , mission[2])