#define ConsolePrint kprintf
int hour, minute, sec = 0, *sec100 = (size_t*)0x09913;
#define ticksPerSecond 10026

void Wait(unsigned int n)
{
	unsigned int ls = (*sec100);
	while ((*sec100) - ls < n)
	{
		__asm__("int $0x41");//Continue execution
		//((void*)(_multitasking2))();
	}
}
void WWait(unsigned int n)
{
	unsigned int ls = (*sec100);
	while ((*sec100) - ls < n)
	{
		__asm__("int $0x41");//Continue execution
							 //((void*)(_multitasking2))();
	}
}



// ------------------------------------------------------------------------------------------------
// I/O Ports

#define IO_RTC_INDEX                    0x70
#define IO_RTC_TARGET                   0x71

// ------------------------------------------------------------------------------------------------
// Indexed Registers

#define REG_SEC                         0x00
#define REG_SEC_ALARM                   0x01
#define REG_MIN                         0x02
#define REG_MIN_ALARM                   0x03
#define REG_HOUR                        0x04
#define REG_HOUR_ALARM                  0x05
#define REG_WEEK_DAY                    0x06
#define REG_DAY                         0x07
#define REG_MONTH                       0x08
#define REG_YEAR                        0x09
#define REG_A                           0x0a
#define REG_B                           0x0b
#define REG_C                           0x0c
#define REG_D                           0x0d

// ------------------------------------------------------------------------------------------------
// General Configuration Registers

#define REGA_UIP                        (1 << 7)    // Update In Progress

#define REGB_HOURFORM                   (1 << 1)    // Hour Format (0 = 12hr, 1 = 24hr)
#define REGB_DM                         (1 << 2)    // Data Mode (0 = BCD, 1 = Binary)

typedef i32 abs_time;     // seconds since Jan 1, 1970 at midnight UTC

						  // ------------------------------------------------------------------------------------------------
						  // Date/Time Components

int g_localTimeZone = +3 * 60;   // Time zone offset in minutes
typedef struct DateTime
{
	int sec;            // [0, 59]
	int min;            // [0, 59]
	int hour;           // [0, 23]
	int day;            // [1, 31]
	int month;          // [1, 12]
	int year;           // [1970, 2038]
	int weekDay;        // [0, 6] sunday = 0
	int yearDay;        // [0, 365]
	int tzOffset;       // offset in minutes
} DateTime;
// ------------------------------------------------------------------------------------------------
static u8 RtcRead(u8 addr)
{
	IoWrite8(IO_RTC_INDEX, addr);
	return IoRead8(IO_RTC_TARGET);
}

// ------------------------------------------------------------------------------------------------
static void RtcWrite(u8 addr, u8 val)
{
	IoWrite8(IO_RTC_INDEX, addr);
	IoWrite8(IO_RTC_TARGET, val);
}

// ------------------------------------------------------------------------------------------------
static u8 BcdToBin(u8 val)
{
	return (val & 0xf) + (val >> 4) * 10;
}

// ------------------------------------------------------------------------------------------------
static u8 BinToBcd(u8 val)
{
	return ((val / 10) << 4) + (val % 10);
}

// ------------------------------------------------------------------------------------------------
void RtcGetTime(DateTime *dt)
{
	// Wait if update is in progress
	if (RtcRead(REG_A) & REGA_UIP)
	{
		PitWait(3);    // up to 488us before update occurs + 1984us to complete
	}

	// Read Registers
	u8 sec = RtcRead(REG_SEC);
	u8 min = RtcRead(REG_MIN);
	u8 hour = RtcRead(REG_HOUR);
	u8 weekDay = RtcRead(REG_WEEK_DAY);
	u8 day = RtcRead(REG_DAY);
	u8 month = RtcRead(REG_MONTH);
	u16 year = RtcRead(REG_YEAR);

	// Get Data configuration
	u8 regb = RtcRead(REG_B);

	// BCD conversion
	if (~regb & REGB_DM)
	{
		sec = BcdToBin(sec);
		min = BcdToBin(min);
		hour = BcdToBin(hour);
		day = BcdToBin(day);
		month = BcdToBin(month);
		year = BcdToBin(year);
	}

	// Century support
	year += 2000;

	// Week day conversion: Sunday as the first day of the week (0-6)
	weekDay--;

	// Write results
	dt->sec = sec;
	dt->min = min;
	dt->hour = hour;
	dt->day = day;
	dt->month = month;
	dt->year = year;
	dt->weekDay = weekDay;
	dt->tzOffset = g_localTimeZone;
}

// ------------------------------------------------------------------------------------------------
void RtcSetTime(const DateTime *dt)
{
	u8 sec = dt->sec;
	u8 min = dt->min;
	u8 hour = dt->hour;
	u8 day = dt->day;
	u8 month = dt->month;
	u8 year = dt->year - 2000;
	u8 weekDay = dt->weekDay + 1;

	// Validate data
	if (sec >= 60 || min >= 60 || hour >= 24 || day > 31 || month > 12 || year >= 100 || weekDay > 7)
	{
		ConsolePrint("RtcSetTime: bad data\n");
		return;
	}

	// Get Data configuration
	u8 regb = RtcRead(REG_B);

	// BCD conversion
	if (~regb & REGB_DM)
	{
		sec = BinToBcd(sec);
		min = BinToBcd(min);
		hour = BinToBcd(hour);
		day = BinToBcd(day);
		month = BinToBcd(month);
		year = BinToBcd(year);
	}

	// Wait if update is in progress
	if (RtcRead(REG_A) & REGA_UIP)
	{
		PitWait(3);    // up to 488us before update occurs + 1984us to complete
	}

	// Write Registers
	RtcWrite(REG_SEC, sec);
	RtcWrite(REG_MIN, min);
	RtcWrite(REG_HOUR, hour);
	RtcWrite(REG_WEEK_DAY, weekDay);
	RtcWrite(REG_DAY, day);
	RtcWrite(REG_MONTH, month);
	RtcWrite(REG_YEAR, year);
}


#define TIME_STRING_SIZE    32



// ------------------------------------------------------------------------------------------------
void SplitTime(DateTime *dt, abs_time t, int tzOffset)
{
	// Adjust t for time zone
	t += tzOffset * 60;

	// Start of each month based on day of the year
	static const int monthStart[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
	static const int leapMonthStart[] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

	// Split time into days since the epoch and seconds in that day
	int epochDays = t / (24 * 60 * 60);
	int daySecs = t % (24 * 60 * 60);

	// Compute time
	int sec = daySecs % 60;
	int min = (daySecs % 3600) / 60;
	int hour = daySecs / 3600;

	// Compute years since the epoch and days in that year
	int epochYears = (epochDays - (epochDays + 365) / 1460) / 365;
	int yearDay = epochDays - (epochYears * 365 + (epochYears + 1) / 4);

	// Adjust year based on epoch
	int year = 1970 + epochYears;

	// Search for month based on days in the year
	const int *mstart = year & 3 ? monthStart : leapMonthStart;

	int month = 1;
	while (yearDay >= mstart[month])
	{
		++month;
	}

	// Compute day of the month and day of the week
	int day = 1 + yearDay - mstart[month - 1];
	int weekDay = (epochDays + 4) % 7;

	// Store results
	dt->sec = sec;
	dt->min = min;
	dt->hour = hour;
	dt->day = day;
	dt->month = month;
	dt->year = year;
	dt->weekDay = weekDay;
	dt->yearDay = yearDay;
	dt->tzOffset = tzOffset;
}

// ------------------------------------------------------------------------------------------------
abs_time JoinTime(const DateTime *dt)
{
	// From the Posix specification (4.14 Seconds Since the Epoch).
	// Could be simplified as the last two cases only apply starting in 2100.
	return
		dt->sec +
		dt->min * 60 +
		dt->hour * 3600 +
		dt->yearDay * 86400 +
		(dt->year - 70) * 31536000 +
		((dt->year - 69) / 4) * 86400 -
		((dt->year - 1) / 100) * 86400 +
		((dt->year + 299) / 400) * 86400;
}

// ------------------------------------------------------------------------------------------------
void FormatTime(char *str, size_t size, const DateTime *dt)
{
	static const char *weekDays[] =
	{
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};

	static const char *months[] =
	{
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};

	uint w = dt->weekDay;
	uint m = dt->month - 1;

	snprintf(str, size, "%s, %02d %s %d %02d:%02d:%02d %02d%02d",
		w < 7 ? weekDays[w] : "XXX",
		dt->day,
		m < 12 ? months[m] : "XXX",
		dt->year, dt->hour, dt->min, dt->sec,
		dt->tzOffset / 60,
		dt->tzOffset % 60);
}