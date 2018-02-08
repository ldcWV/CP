MAP_HEIGHT_MIN = 20
MAP_HEIGHT_MAX = 50
MAP_WIDTH_MIN = 20
MAP_WIDTH_MAX = 50
MAP_KARBONITE_MIN = 0
MAP_KARBONITE_MAX = 50
ASTEROID_ROUND_MIN = 10
ASTEROID_ROUND_MAX = 20
ASTEROID_KARB_MIN = 20
ASTEROID_KARB_MAX = 100
ORBIT_FLIGHT_MIN = 50
ORBIT_FLIGHT_MAX = 200
ROUND_LIMIT = 1000


def validate_map_dims(h, w):
    return (MAP_HEIGHT_MAX >= h >= MAP_HEIGHT_MIN) and (MAP_WIDTH_MAX >= w >= MAP_WIDTH_MIN)

def validate_num_bots(bot_list):
    return 0 < len(bot_list) <= 6 and (len(bot_list) % 2 == 0)

def validate_asteroid_pattern(asteroid_list):
    rounds = [i[0] for i in asteroid_list]
    karb = [i[1] for i in asteroid_list]
    for i in range(len(rounds)):
        if rounds[i] < 1 or rounds[i] > ROUND_LIMIT:
            print("fail round limit check")
            return False
        if karb[i] < ASTEROID_KARB_MIN or karb[i] > ASTEROID_KARB_MAX:
            print("fail karb limit check")
            return False
    rounds.sort()
    if rounds[0] > ASTEROID_ROUND_MAX:
        print("fail minimum round")
        return False
    if ROUND_LIMIT - rounds[-1] > ASTEROID_ROUND_MAX:
        print("fail maximum round")
        return False
    for i in range(len(rounds) - 1):
        diff = rounds[i+1] - rounds[i]
        if diff < ASTEROID_ROUND_MIN or diff > ASTEROID_ROUND_MAX:
            print("fail diff {}".format(diff))
            return False
    return True

def validate_orbital_pattern(amplitude, period, center):
    if center - amplitude < ORBIT_FLIGHT_MIN:
        return False
    if center + amplitude > ORBIT_FLIGHT_MAX:
        return False
    return True