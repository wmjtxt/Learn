from django.shortcuts import render
from django.http import HttpResponse

from .models import Board

# Create your views here.

# 1
#def home(request):
#    return HttpResponse('Hello World!')
# 2
#def home(request):
#    boards = Board.objects.all()
#    boards_names = list()
#
#    for board in boards:
#        boards_names.append(board.name)
#    print(boards_names)
#    response_html = '<br>'.join(boards_names)
#    
#    return HttpResponse(response_html)
# 3
def home(request):
    boards = Board.objects.all()
    #print(boards)
    return render(request, 'home.html', {'boards': boards})
