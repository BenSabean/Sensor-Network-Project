import MySQLdb

class DataEntry:  

	def __init__(self, myHost, myUser, myPasswd, myDb):
		self.db=MySQLdb.connect(host=myHost,user=myUser,
                  passwd=myPasswd,db=myDb)

		self.c=self.db.cursor()

	def close(self):
		self.db.close() 

	def getTable(self, table):
		self.c.execute("SELECT * FROM " + table)
		return self.c.fetchall()

	def insertData(self, name, studentNum, age):
		try:
   			self.c.execute("""INSERT INTO `table1` (`Name`, `student number`, `Age`) VALUES (%s,%s,%s)""",(name,studentNum,age))
   			self.db.commit()
			return True
		except:
   			self.db.rollback() 
 			return False
