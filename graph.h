WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
﻿/************************************
* 交通图导航系统 vC.A.0
************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define FILE_NAME "graph.txt"

/* 顶点状态 */
enum {
    VERTEX_STATE_VALID,     /* 有效顶点 */
    VERTEX_STATE_REMOVE,    /* 删除顶点 */
};

/* 顶点信息 */
typedef struct _tVertex {
    char name[256];         /* 顶点名称 */
    char info[1024];        /* 顶点描述 */
    int state;              /* 顶点状态 */
} Vertex;

/* 顶点信息列表 */
typedef struct _tVertexList {
    Vertex* data;           /* 顶点数组 */
    int size;               /* 顶点个数 */
    int capacity;           /* 列表容量 */
} VertexList;

/* 创建顶点信息列表 */
VertexList* createVertexList() {
    VertexList* list = (VertexList*)malloc(sizeof(VertexList));
    memset(list, 0, sizeof(VertexList));
    return list;
}

/* 销毁顶点信息列表 */
void freeVertexList(VertexList* list) {
    if (list) {
        if (list->data) {
            free(list->data);
        }
        free(list);
    }
}

/* 往顶点信息列表添加顶点信息 */
void addVertexList(VertexList* list, Vertex* vertex) {
    if (list) {
        if (list->size == list->capacity) {
            list->capacity = list->capacity ? list->capacity * 2 : 16;
            if (list->data) {
                list->data = (Vertex*)realloc(list->data, sizeof(list->data[0]) * list->capacity);
            } else {
                list->data = (Vertex*)malloc(sizeof(list->data[0]) * list->capacity);
            }
        }
        list->data[list->size++] = *vertex;
    }
}

/* 从顶点信息列表中查找索引 */
int findVertexListByName(VertexList* list, const char name[]) {
    if (list) {
        for (int index = 0; index < list->size; ++index) {
            Vertex* vertex = &list->data[index];
            if (strcmp(vertex->name, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}

/* 权重个数 */
#define WEIGHT_LEN 2
/* 无穷大 */
#define __INFINITY__ 9999999

/* 顶点访问标识 */
enum {
    VISIT_STATE_VOID,   /*未访问*/
    VISIT_STATE_MARK    /*已访问*/
};

/* 边的权重类型 */
enum {
    EDGE_WEIGHT_DIST,   /* 地铁 */
    EDGE_WEIGHT_TIME,   /* 公交 */
};

/* 权重类型 */
typedef double WEIGHT_TYPE;

/* 边信息 */
typedef struct _tEdge {
    int begin;          /*起点索引*/
    int end;            /*终点索引*/
    WEIGHT_TYPE weight[WEIGHT_LEN];     /* 权重 */
} Edge;

/* 边信息列表 */
typedef struct _tEdgeList {
    Edge* data;         /* 边数组 */
    int size;           /* 边个数 */
    int capacity;       /* 数组容量 */
} EdgeList;

/* 创建边信息列表 */
EdgeList* createEdgeList() {
    EdgeList* list = (EdgeList*)malloc(sizeof(EdgeList));
    memset(list, 0, sizeof(EdgeList));
    return list;
}

/* 销毁边信息列表 */
void freeEdgeList(EdgeList* list) {
    if (list) {
        if (list->data) {
            free(list->data);
        }
        free(list);
    }
}

/* 从边信息列表搜索信息 */
int findEdgeList(EdgeList* list, int begin, int end) {
    if (list) {
        for (int index = 0; index < list->size; ++index) {
            Edge* edge = &list->data[index];
            if (edge->begin == begin && edge->end == end) {
                return index;
            }
        }
    }
    return -1;
}

/* 往边信息列表添加边信息 */
void addEdgeList(EdgeList* list, Edge* edge) {
    if (list) {
        if (list->size == list->capacity) {
            list->capacity = list->capacity ? list->capacity * 2 : 16;
            if (list->data) {
                list->data = (Edge*)realloc(list->data, sizeof(list->data[0]) * list->capacity);
            } else {
                list->data = (Edge*)malloc(sizeof(list->data[0]) * list->capacity);
            }
        }
        list->data[list->size++] = *edge;
    }
}

/* 从边信息列表删除边信息 */
void removeEdgeList(EdgeList* list, int begin, int end) {
    if (list) {
        int position = findEdgeList(list, begin, end);
        if (position != -1) {
            for (int index = position; index < list->size; ++index) {
                list->data[index] = list->data[index + 1];
            }
            --list->size;
        }
    }
}

/* 往边信息列表更新信息 */
void updateEdgeList(EdgeList* list, Edge* edge) {
    if (list) {
        int position = findEdgeList(list, edge->begin, edge->end);
        if (position != -1) {
            list->data[position] = *edge;
        } else {
            addEdgeList(list, edge);
        }
    }
}

/* 图信息结构体 */
typedef struct _tGraph {
    VertexList* vertex;     /* 顶点 */
    EdgeList* edge;         /* 边 */
} Graph;

/* 创建图信息列表 */
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    memset(graph, 0, sizeof(Graph));
    graph->vertex = createVertexList();
    graph->edge = createEdgeList();
    return graph;
}

/* 销毁图信息列表 */
void freeGraph(Graph* graph) {
    if (graph) {
        if (graph->vertex) {
            free(graph->vertex);
        }
        if (graph->edge) {
            free(graph->edge);
        }
        free(graph);
    }
}

/* 加载图信息 */
Graph* loadGraph(const char filename[]) {
    Graph* graph = createGraph();
    FILE* input = fopen(filename, "r");
    if (input) {
        int vertex_count = 0;
        int edge_count = 0;

        if (fscanf(input, "%d %d", &vertex_count, &edge_count) == 2) {
            for (int index = 0; index < vertex_count; ++index) {
                Vertex vertex;
                memset(&vertex, 0, sizeof(Vertex));
                int x, y;
                if (fscanf(input, "%s %s %d %d", vertex.name, vertex.info, &x, &y) == 4) {
                    addVertexList(graph->vertex, &vertex);
                } else {
                    printf("error: load vectex failed!\n");
                }
            }

            for (int index = 0; index < edge_count; ++index) {
                Edge edge;
                memset(&edge, 0, sizeof(Edge));
                char begin[256] = { 0 };
                char end[256] = { 0 };
                if (fscanf(input, "%s %s %lf %lf", begin, end, &edge.weight[EDGE_WEIGHT_DIST], &edge.weight[EDGE_WEIGHT_TIME]) == 4) {
                    edge.begin = findVertexListByName(graph->vertex, begin);
                    if (edge.begin == -1) {
                        printf("error: load edge '%s' is not found!\n", begin);
                        continue;
                    }
                    edge.end = findVertexListByName(graph->vertex, end);
                    if (edge.end == -1) {
                        printf("error: load edge '%s' is not found!\n", end);
                        continue;
                    }
                    updateEdgeList(graph->edge, &edge);
                } else {
                    printf("error: load edge failed!\n");
                }
            }
        }

        fclose(input);
    }
    return graph;
}

typedef double WEIGHT_TYPE;

/* 邻接矩阵结构体 */
typedef struct _tAdjMatrix {
    WEIGHT_TYPE** data;     /* 二维矩阵 */
    int size;               /* 矩阵尺寸 */
} AdjMatrix;

/* 创建邻接矩阵 */
AdjMatrix* createAdjMatrix(int size) {
    AdjMatrix* matrix = (AdjMatrix*)malloc(sizeof(AdjMatrix));
    memset(matrix, 0, sizeof(AdjMatrix));
    matrix->size = size;
    matrix->data = (WEIGHT_TYPE**)malloc(sizeof(WEIGHT_TYPE*) * size);
    for (int i = 0; i < size; ++i) {
        matrix->data[i] = (WEIGHT_TYPE*)malloc(sizeof(WEIGHT_TYPE) * size);
        for (int j = 0; j < size; ++j) {
            matrix->data[i][j] = __INFINITY__;
        }
    }
    return matrix;
}

/* 销毁邻接矩阵 */
void freeAdjMatrix(AdjMatrix* matrix) {
    if (matrix) {
        for (int index = 0; index < matrix->size; ++index) {
            free(matrix->data[index]);
        }
        free(matrix);
    }
}

/* 队列结构体 */
typedef struct _tQueue {
    int* data;          /* 数据 */
    int front;          /* 头位置 */
    int tail;           /* 尾位置 */
    int count;          /* 数量 */
    int capacity;       /* 容量 */
}Queue;

/* 创建队列 */
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue) {
        memset(queue, 0, sizeof(Queue));
        queue->data = (int*)malloc(capacity * sizeof(int));
        queue->capacity = capacity;
    }
    return queue;
}

/* 销毁队列 */
void freeQueue(Queue* queue) {
    if (queue) {
        if (queue->data) {
            free(queue->data);
        }
        free(queue);
    }
}

/* 进入队列 */
void enqueueQueue(Queue* queue, int data) {
    if (queue) {
        if (queue->count < queue->capacity) {
            queue->data[queue->tail] = data;
            queue->tail = (queue->tail + 1) % queue->capacity;
            ++queue->count;
        }
    }
}

/* 离开队列 */
int dequeueQueue(Queue* queue) {
    int point = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    --queue->count;
    return point;
}

/* 获取队列前项元素 */
int* frontQueue(Queue* queue) {
    if (queue) {
        if (queue->count > 0) {
            return &queue->data[queue->front];
        }
    }
    return NULL;
}

/* 获取迪杰斯特拉未遍历顶点中权值最小的顶点 */
int getDijkstraMinimum(int* visit, WEIGHT_TYPE* dis, int len) {
    int index, min = -1;
    for (index = 0; index < len; ++index) {
        /* 未遍历顶点 */
        if (visit[index] == VISIT_STATE_VOID) {
            if (min == -1) {
                min = index;
            } else {
                if (dis[min] > dis[index]) {
                    min = index;
                }
            }
        }
    }
    return min;
}

/* 迪杰斯特拉算法 */
int* dijkstraPath(Graph* graph, int begin, int end, int position, WEIGHT_TYPE* distance) {
    if (graph) {
        AdjMatrix* matrix = createAdjMatrix(graph->vertex->size);
        for (int index = 0; index < graph->edge->size; ++index) {
            Edge* edge = &graph->edge->data[index];
            matrix->data[edge->begin][edge->end] = edge->weight[position];
        }

        int* visit = (int*)malloc(sizeof(int) * matrix->size);
        int* path = (int*)malloc(sizeof(int) * matrix->size);
        WEIGHT_TYPE* dis = (WEIGHT_TYPE*)malloc(sizeof(WEIGHT_TYPE) * matrix->size);
        for (int index = 0; index < matrix->size; ++index) {
            visit[index] = VISIT_STATE_VOID;
            path[index] = -1;
            dis[index] = __INFINITY__;
        }

        dis[begin] = 0;
        while (1) {
            int min = getDijkstraMinimum(visit, dis, matrix->size);
            if (min == -1) break;
            visit[min] = VISIT_STATE_MARK;
            for (int to = 0; to < matrix->size; ++to) {
                if (visit[to] == VISIT_STATE_VOID) {
                    WEIGHT_TYPE weight = matrix->data[min][to];
                    /* 两点间存在邻接关系 */
                    if (weight < __INFINITY__) {
                        /*松弛成功*/
                        if ((dis[min] + weight) < dis[to]) {
                            dis[to] = dis[min] + weight;
                            path[to] = min;
                        }
                    }
                }
            }
        }
        *distance = dis[end];
        freeAdjMatrix(matrix);
        free(visit);
        if (path[end] == -1) {
            free(path);
        } else {
            return path;
        }
    }
    return NULL;
}

/* 广度优先搜索算法 */
int* bfsPath(Graph* graph, int begin, int end) {
    if (graph) {
        AdjMatrix* matrix = createAdjMatrix(graph->vertex->size);
        for (int index = 0; index < graph->edge->size; ++index) {
            Edge* edge = &graph->edge->data[index];
            matrix->data[edge->begin][edge->end] = 1;
        }

        int* visit = (int*)malloc(sizeof(int) * matrix->size);
        int* path = (int*)malloc(sizeof(int) * matrix->size);
        for (int index = 0; index < matrix->size; ++index) {
            visit[index] = VISIT_STATE_VOID;
            path[index] = -1;
        }

        Queue* queue = createQueue(graph->vertex->size);
        enqueueQueue(queue, begin);

        while (frontQueue(queue)) {
            int cursor = dequeueQueue(queue);
            if (cursor == end) {
                break;
            } else {
                if (visit[cursor] == VISIT_STATE_VOID) {
                    visit[cursor] = VISIT_STATE_MARK;
                    for (int index = 0; index < matrix->size; ++index) {
                        if (visit[index] == VISIT_STATE_VOID && matrix->data[cursor][index] != __INFINITY__) {
                            path[index] = cursor;
                            enqueueQueue(queue, index);
                        }
                    }
                }
            }
        }

        freeAdjMatrix(matrix);
        freeQueue(queue);
        free(visit);
        if (path[end] == -1) {
            free(path);
        } else {
            return path;
        }
    }
    return NULL;
}
